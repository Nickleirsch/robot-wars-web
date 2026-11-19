"use client";

import type { SimState, TurnEvent } from "@/lib/types";
import { RobotIcon } from "@/components/RobotIcon";

interface Props {
  state: SimState;
  events: TurnEvent[];
}

export function Battlefield({ state, events }: Props) {
  const { rows, cols, robots } = state;

  // Cell centres as percentages, so the board scales with its container.
  const cx = (y: number) => ((y + 0.5) / cols) * 100;
  const cy = (x: number) => ((x + 0.5) / rows) * 100;
  const cellPct = 100 / Math.max(rows, cols);

  const tokenSize = `calc(${(1 / cols) * 100}% - 2px)`;

  return (
    <div className="board">
      <div
        className="cells"
        style={{
          gridTemplateColumns: `repeat(${cols}, 1fr)`,
          gridTemplateRows: `repeat(${rows}, 1fr)`,
        }}
      >
        {Array.from({ length: rows * cols }, (_, i) => (
          <div key={i} className="cell" />
        ))}
      </div>

      {/* One marker layer per turn: keying on the turn number restarts the
          CSS animations even when the same cell is hit twice in a row. */}
      {events.map((e, i) => {
        if (e.kind === "move" || e.kind === "step") return null;
        const size = e.kind === "kill" ? cellPct * 2.4 : cellPct * 1.1;
        return (
          <div
            key={`${state.turn}-${i}`}
            className={`marker ${e.kind}`}
            style={{
              left: `${cx(e.y)}%`,
              top: `${cy(e.x)}%`,
              width: `${size}%`,
              aspectRatio: "1 / 1",
            }}
          />
        );
      })}

      {robots
        .filter((r) => r.alive)
        .map((r) => (
          <div
            key={r.name}
            className="token"
            title={`${r.name} (${r.type}) at ${r.x} x ${r.y}: ${r.kills} kills, ${r.deaths} deaths`}
            style={{
              left: `${cx(r.y)}%`,
              top: `${cy(r.x)}%`,
              width: tokenSize,
              height: tokenSize,
              marginLeft: `calc(-0.5 * ${tokenSize})`,
              marginTop: `calc(-0.5 * ${tokenSize})`,
            }}
          >
            <RobotIcon type={r.type} size="100%" />
          </div>
        ))}
    </div>
  );
}
