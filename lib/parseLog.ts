import type { TurnEvent } from "./types";

// The C++ engine reports each turn as plain text. Rather than change every
// robot's turn() to emit structured data, we parse the lines it already
// produces so the board can draw shots, kills and revives.
//
//   Mold - M (Madbot):
//   Fired at 2 x 7 but missed.
//   Fired at 9 x 1 killing O
//   Moved to 5 x 7
//   Stepped on C at 6 x 8
//   Orion - O (RoboTank) is being revived at 0 x 0

const HEADER = /^(.+?)\s+-\s+(\S)\s+\((.+?)\):\s*$/;
const REVIVE = /^(.+?)\s+-\s+(\S)\s+\((.+?)\)\s+is being revived at (\d+) x (\d+)/;
const FIRE_MISS = /^Fired at (\d+) x (\d+) but missed/;
const FIRE_KILL = /^Fired at (\d+) x (\d+) killing (\S)/;
const MOVED = /^Moved to (\d+) x (\d+)/;
const STEPPED = /^Stepped on (\S) at (\d+) x (\d+)/;

export function parseTurnLog(log: string): TurnEvent[] {
  const events: TurnEvent[] = [];
  let actor = "?";

  for (const raw of log.split("\n")) {
    const line = raw.trim();
    if (!line) continue;

    const revive = REVIVE.exec(line);
    if (revive) {
      events.push({ kind: "revive", actor: revive[2], x: +revive[4], y: +revive[5] });
      continue;
    }

    const header = HEADER.exec(line);
    if (header) {
      actor = header[2];
      continue;
    }

    let m: RegExpExecArray | null;
    if ((m = FIRE_KILL.exec(line))) {
      events.push({ kind: "kill", actor, x: +m[1], y: +m[2], victim: m[3] });
    } else if ((m = FIRE_MISS.exec(line))) {
      events.push({ kind: "fire", actor, x: +m[1], y: +m[2] });
    } else if ((m = STEPPED.exec(line))) {
      events.push({ kind: "step", actor, x: +m[2], y: +m[3], victim: m[1] });
    } else if ((m = MOVED.exec(line))) {
      events.push({ kind: "move", actor, x: +m[1], y: +m[2] });
    }
  }

  return events;
}
