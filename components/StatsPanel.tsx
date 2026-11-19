"use client";

import type { SimState } from "@/lib/types";
import { colourFor } from "@/lib/presets";
import { RobotIcon } from "@/components/RobotIcon";

export function StatsPanel({ state }: { state: SimState }) {
  return (
    <>
      <div className="panel">
        <h2>Robots: {state.listSize} in the battle</h2>
        <div className="robot-cards">
          {state.robots.map((r) => (
            <div key={r.name} className={`robot-card${r.alive ? "" : " dead"}`}>
              <div className="icon">
                <RobotIcon type={r.type} size={34} />
              </div>
              <div className="who">
                <b>{r.name}</b>
                <span style={{ color: colourFor(r.type) }}>{r.type}</span>
              </div>
              <div className="kd">
                <b>{r.kills}</b> kills
                <br />
                {r.deaths} deaths
              </div>
            </div>
          ))}
        </div>
      </div>

      <div className="panel">
        <h2>Respawn queue</h2>
        {state.queue.length === 0 ? (
          <p className="empty">Empty. Nobody is waiting to respawn.</p>
        ) : (
          <div className="queue">
            {state.queue.map((name, i) => (
              <span key={name} className="qitem">
                {i + 1}. {name}
              </span>
            ))}
          </div>
        )}
      </div>
    </>
  );
}
