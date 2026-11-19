"use client";

import { parseTurnGroups, type ActionKind } from "@/lib/turnLog";
import { colourFor } from "@/lib/presets";
import { RobotIcon } from "@/components/RobotIcon";

const TAG: Record<ActionKind, string> = {
  fire: "Shot",
  kill: "Kill",
  move: "Move",
  step: "Stomp",
  revive: "Respawn",
};

export function LogPanel({ log, turn }: { log: string; turn: number }) {
  const groups = parseTurnGroups(log);
  const count = (kind: ActionKind) =>
    groups.reduce((n, g) => n + g.actions.filter((a) => a.kind === kind).length, 0);

  return (
    <div className="panel turn-log">
      <div className="tl-head">
        <h2>Turn {turn}</h2>
        {groups.length > 0 && (
          <div className="tl-chips">
            <span className="tl-chip fire">{count("fire")} shots</span>
            <span className="tl-chip kill">{count("kill")} kills</span>
            <span className="tl-chip move">{count("move")} moves</span>
            <span className="tl-chip step">{count("step")} stomps</span>
          </div>
        )}
      </div>

      {groups.length === 0 ? (
        <p className="empty">Step or play to see what each robot did this turn.</p>
      ) : (
        <div className="tl-scroll">
          {groups.map((g) => (
            <div key={g.name} className="tl-group">
              <div className="tl-who">
                <RobotIcon type={g.type} size={26} />
                <b>{g.name}</b>
                <span style={{ color: colourFor(g.type) }}>{g.type}</span>
              </div>
              <ul>
                {g.actions.map((a, i) => (
                  <li key={i}>
                    <span className={`tl-tag ${a.kind}`}>{TAG[a.kind]}</span>
                    {a.text}
                  </li>
                ))}
              </ul>
            </div>
          ))}
        </div>
      )}
    </div>
  );
}
