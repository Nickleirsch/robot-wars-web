"use client";

import { useEffect, useState } from "react";
import { useSimulation } from "@/lib/useSimulation";
import { Battlefield } from "@/components/Battlefield";
import { StatsPanel } from "@/components/StatsPanel";
import { LogPanel } from "@/components/LogPanel";
import { RobotIcon } from "@/components/RobotIcon";
import { Tutorial } from "@/components/Tutorial";
import { DEFAULT_PRESET, PRESETS, TYPE_COLOURS } from "@/lib/presets";

export default function Page() {
  const sim = useSimulation();
  const [preset, setPreset] = useState(DEFAULT_PRESET);
  const [config, setConfig] = useState(PRESETS[DEFAULT_PRESET]);
  const [seed, setSeed] = useState(12345);
  const [showConfig, setShowConfig] = useState(false);

  // Kick off a first run as soon as the wasm module is up.
  useEffect(() => {
    if (sim.engineReady) sim.start(config, seed);
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [sim.engineReady]);

  const choosePreset = (name: string) => {
    setPreset(name);
    setConfig(PRESETS[name]);
    sim.start(PRESETS[name], seed);
  };

  const restart = () => sim.start(config, seed);
  const randomise = () => {
    const next = Math.floor(Math.random() * 1_000_000);
    setSeed(next);
    sim.start(config, next);
  };

  const { state } = sim;
  const done = state?.finished ?? false;

  return (
    <div className="page">
      <header className="title">
        <h1>Robot Wars</h1>
      </header>

      {sim.error && <div className="error">{sim.error}</div>}

      <div className="controls">
        <button
          className="btn primary"
          onClick={() => sim.setPlaying(!sim.playing)}
          disabled={!state || done}
        >
          {sim.playing ? "Pause" : "Play"}
        </button>
        <button className="btn" onClick={sim.step} disabled={!state || sim.playing || done}>
          Step
        </button>
        <button className="btn" onClick={restart} disabled={!sim.engineReady}>
          Restart
        </button>
        <button className="btn" onClick={randomise} disabled={!sim.engineReady}>
          New seed
        </button>

        <label className="field">
          Map
          <select value={preset} onChange={(e) => choosePreset(e.target.value)}>
            {Object.keys(PRESETS).map((name) => (
              <option key={name}>{name}</option>
            ))}
          </select>
        </label>

        <label className="field">
          Seed
          <input
            type="number"
            value={seed}
            onChange={(e) => setSeed(Number(e.target.value))}
            onBlur={restart}
          />
        </label>

        <label className="field">
          Speed
          <input
            type="range"
            min={60}
            max={1200}
            step={20}
            value={1260 - sim.speed}
            onChange={(e) => sim.setSpeed(1260 - Number(e.target.value))}
          />
        </label>

        <button className="btn" onClick={() => setShowConfig(true)}>
          Config
        </button>

        <span className="turnbadge">
          Turn <b>{state?.turn ?? 0}</b> / {state?.totalSteps ?? 0}
          {done && " (finished)"}
        </span>
      </div>

      <div className="layout">
        <div className="panel board-panel">
          {state ? (
            <Battlefield state={state} events={sim.events} />
          ) : (
            <p className="empty">
              {sim.engineReady ? "No simulation loaded." : "Loading the WebAssembly engine…"}
            </p>
          )}
          <div className="legend">
            {Object.entries(TYPE_COLOURS).map(([type]) => (
              <span key={type}>
                <RobotIcon type={type} size={22} />
                {type}
              </span>
            ))}
          </div>
        </div>

        <aside>
          <Tutorial />
          {state && <StatsPanel state={state} />}
          <LogPanel log={sim.log} turn={state?.turn ?? 0} />
        </aside>
      </div>

      {showConfig && (
        <div className="modal-backdrop" onClick={() => setShowConfig(false)}>
          <div
            className="modal panel"
            role="dialog"
            aria-label="Battlefield config"
            onClick={(e) => e.stopPropagation()}
          >
            <h2>Battlefield config</h2>
            <p className="empty">
              Same .txt format the desktop build reads. Edit it to change the map, step count or
              roster.
            </p>
            <textarea
              className="config"
              value={config}
              spellCheck={false}
              onChange={(e) => setConfig(e.target.value)}
            />
            <div className="modal-actions">
              <button className="btn" onClick={() => setShowConfig(false)}>
                Close
              </button>
              <button
                className="btn primary"
                onClick={() => {
                  restart();
                  setShowConfig(false);
                }}
              >
                Run this config
              </button>
            </div>
          </div>
        </div>
      )}
    </div>
  );
}
