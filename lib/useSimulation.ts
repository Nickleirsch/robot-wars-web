"use client";

import { useCallback, useEffect, useRef, useState } from "react";
import type { SimState, TurnEvent } from "./types";
import { parseTurnLog } from "./parseLog";

interface NativeSimulation {
  init(config: string, seed: number): boolean;
  step(): boolean;
  snapshot(): string;
  log(): string;
  error(): string;
  delete(): void;
}

interface RobotWarsModule {
  Simulation: new () => NativeSimulation;
}

// The wasm glue lives in public/ and is fetched at runtime. Going through
// `new Function` keeps webpack and turbopack from trying to resolve and bundle
// it at build time -- it is a plain static asset, not a dependency.
const importAtRuntime = new Function("url", "return import(url)") as (
  url: string,
) => Promise<{ default: () => Promise<RobotWarsModule> }>;

let modulePromise: Promise<RobotWarsModule> | null = null;

function loadEngine(): Promise<RobotWarsModule> {
  if (!modulePromise) {
    modulePromise = importAtRuntime("/wasm/robotwars.mjs").then((m) => m.default());
  }
  return modulePromise;
}

export function useSimulation() {
  const simRef = useRef<NativeSimulation | null>(null);
  const [engineReady, setEngineReady] = useState(false);
  const [state, setState] = useState<SimState | null>(null);
  const [events, setEvents] = useState<TurnEvent[]>([]);
  const [log, setLog] = useState("");
  const [error, setError] = useState<string | null>(null);
  const [playing, setPlaying] = useState(false);
  const [speed, setSpeed] = useState(500); // ms per turn

  useEffect(() => {
    let cancelled = false;
    loadEngine()
      .then((mod) => {
        if (cancelled) return;
        simRef.current = new mod.Simulation();
        setEngineReady(true);
      })
      .catch((e) => setError(`Failed to load the wasm engine: ${e}`));
    return () => {
      cancelled = true;
    };
  }, []);

  const readState = useCallback(() => {
    const sim = simRef.current;
    if (!sim) return;
    setState(JSON.parse(sim.snapshot()) as SimState);
  }, []);

  const start = useCallback(
    (config: string, seed: number) => {
      const sim = simRef.current;
      if (!sim) return;
      setPlaying(false);
      setLog("");
      setEvents([]);
      if (!sim.init(config, seed >>> 0)) {
        setError(sim.error());
        setState(null);
        return;
      }
      setError(null);
      readState();
    },
    [readState],
  );

  const step = useCallback(() => {
    const sim = simRef.current;
    if (!sim) return false;
    const advanced = sim.step();
    if (!advanced) {
      setPlaying(false);
      return false;
    }
    const turnLog = sim.log();
    setLog(turnLog);
    setEvents(parseTurnLog(turnLog));
    readState();
    return true;
  }, [readState]);

  // Playback loop. Re-armed on every tick so speed changes take effect at once.
  useEffect(() => {
    if (!playing) return;
    const id = window.setTimeout(() => {
      if (!step()) setPlaying(false);
    }, speed);
    return () => window.clearTimeout(id);
  }, [playing, speed, step, state?.turn]);

  useEffect(() => {
    if (state?.finished) setPlaying(false);
  }, [state?.finished]);

  return {
    engineReady,
    state,
    events,
    log,
    error,
    playing,
    speed,
    setSpeed,
    setPlaying,
    start,
    step,
  };
}
