"use client";

import { useEffect, useState } from "react";
import { RobotIcon } from "@/components/RobotIcon";

const ROSTER: { name: string; type: string; action: string }[] = [
  {
    name: "Mold",
    type: "Madbot",
    action:
      "Does not move. Fires once at a random square next to it. Upgrades to Orion after 3 kills.",
  },
  {
    name: "Orion",
    type: "RoboTank",
    action:
      "Does not move. Fires once at a random square anywhere on the board. Upgrades to Ultrabot after 3 kills.",
  },
  {
    name: "T-1000",
    type: "Terminator",
    action:
      "Only moves. If a robot is next to it, it steps onto that robot and kills it. Otherwise it moves to a random empty square next to it. Upgrades to Chrono after 3 kills.",
  },
  {
    name: "Bast",
    type: "BlueThunder",
    action:
      "Does not move. Each turn it fires once in the next direction of a ring of 8 squares around itself. Upgrades to Mold after 3 kills.",
  },
  {
    name: "Seneca",
    type: "Sentinel",
    action:
      "Moves to a random empty square next to it, then fires twice at random squares in the top-left corner of the board.",
  },
  {
    name: "Ra-One",
    type: "RoboCop",
    action:
      "Moves to a random square next to it, then fires three times at random squares in the top-left corner. Upgrades to Chrono after 3 kills.",
  },
  {
    name: "Chrono",
    type: "T-RoboCop",
    action:
      "If a robot is next to it, it steps onto that robot and kills it. Otherwise it moves to a random empty square next to it. Then it fires three times in the top-left corner. Upgrades to Ultrabot after 3 kills.",
  },
  {
    name: "Ultrabot",
    type: "UltimateRobot",
    action:
      "If a robot is next to it, it steps onto that robot and kills it. Otherwise it moves to a random empty square next to it. Then it fires three times at random squares anywhere on the board.",
  },
  {
    name: "Nimrod",
    type: "PrimeSentinel",
    action:
      "Moves to a random square next to it. If a robot is there, it kills it. Then it fires twice at random squares anywhere on the board.",
  },
];

export function Tutorial() {
  const [open, setOpen] = useState(false);

  // Close the drawer with the Escape key.
  useEffect(() => {
    if (!open) return;
    const onKey = (e: KeyboardEvent) => {
      if (e.key === "Escape") setOpen(false);
    };
    window.addEventListener("keydown", onKey);
    return () => window.removeEventListener("keydown", onKey);
  }, [open]);

  return (
    <>
      {!open && (
        <button
          className="tutorial-tab"
          onClick={() => setOpen(true)}
          aria-expanded={open}
          aria-controls="tutorial-drawer"
        >
          How to play
        </button>
      )}

      {open && (
        <aside id="tutorial-drawer" className="tutorial-drawer" aria-label="How to play">
          <div className="tutorial-head">
            <h2>How to play</h2>
            <button className="btn" onClick={() => setOpen(false)}>
              Close
            </button>
          </div>

          <ol className="tutorial-steps">
            <li>
              <b>Pick a map</b> from the Map menu. Each one is a grid with a set of robots placed
              on it.
            </li>
            <li>
              <b>Press Play</b> to watch the battle, or <b>Step</b> to move it forward one robot
              at a time. Use the Speed slider to control how fast it runs.
            </li>
            <li>
              Every turn, robots act in queue order. A robot that is hit is knocked out, then
              revived later on a random empty square. After its third knock-out it is out for
              good.
            </li>
            <li>
              Use <b>New seed</b> for a different battle, or keep the same seed to replay one
              exactly.
            </li>
            <li>
              Open <b>Config</b> to change the map, number of steps or robots. Format: one line per
              robot as <code>Type Name row column</code>, or <code>random</code> for either
              position.
            </li>
          </ol>

          <h3 className="tutorial-sub">The robots</h3>
          <ul className="tutorial-roster">
            {ROSTER.map((r) => (
              <li key={r.name}>
                <span className="tutorial-icon">
                  <RobotIcon type={r.type} size={30} />
                </span>
                <span className="tutorial-body">
                  <b>{r.name}</b> <span className="tutorial-type">{r.type}</span>
                  <span className="tutorial-action">{r.action}</span>
                </span>
              </li>
            ))}
          </ul>
          <p className="empty">
            Each robot is drawn as its own figure on the board. Dimmed robots are out of action
            until they are revived.
          </p>
        </aside>
      )}
    </>
  );
}
