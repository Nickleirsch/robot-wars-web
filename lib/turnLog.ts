// Groups the engine's plain-text turn log by robot, so the UI can show
// "who did what" instead of raw lines. Same text format as parseLog.ts.

export type ActionKind = "fire" | "kill" | "move" | "step" | "revive";

export interface TurnAction {
  kind: ActionKind;
  text: string;
}

export interface TurnGroup {
  name: string;
  initial: string;
  type: string;
  actions: TurnAction[];
}

const HEADER = /^(.+?)\s+-\s+(\S)\s+\((.+?)\):\s*$/;
const REVIVE = /^(.+?)\s+-\s+(\S)\s+\((.+?)\)\s+is being revived at (\d+) x (\d+)/;
const FIRE_MISS = /^Fired at (\d+) x (\d+) but missed/;
const FIRE_KILL = /^Fired at (\d+) x (\d+) killing (\S)/;
const MOVED = /^Moved to (\d+) x (\d+)/;
const STEPPED = /^Stepped on (\S) at (\d+) x (\d+)/;

export function parseTurnGroups(log: string): TurnGroup[] {
  const groups: TurnGroup[] = [];
  let current: TurnGroup | null = null;

  const groupFor = (name: string, initial: string, type: string): TurnGroup => {
    let g = groups.find((x) => x.name === name);
    if (!g) {
      g = { name, initial, type, actions: [] };
      groups.push(g);
    }
    return g;
  };

  for (const raw of log.split("\n")) {
    const line = raw.trim();
    if (!line) continue;

    let m: RegExpExecArray | null;
    if ((m = REVIVE.exec(line))) {
      current = groupFor(m[1], m[2], m[3]);
      current.actions.push({ kind: "revive", text: `respawned at ${m[4]} x ${m[5]}` });
      continue;
    }
    if ((m = HEADER.exec(line))) {
      current = groupFor(m[1], m[2], m[3]);
      continue;
    }
    if (!current) continue;

    if ((m = FIRE_KILL.exec(line))) {
      current.actions.push({ kind: "kill", text: `destroyed ${m[3]} at ${m[1]} x ${m[2]}` });
    } else if ((m = FIRE_MISS.exec(line))) {
      current.actions.push({ kind: "fire", text: `fired at ${m[1]} x ${m[2]}, missed` });
    } else if ((m = STEPPED.exec(line))) {
      current.actions.push({ kind: "step", text: `stomped ${m[1]} at ${m[2]} x ${m[3]}` });
    } else if ((m = MOVED.exec(line))) {
      current.actions.push({ kind: "move", text: `moved to ${m[1]} x ${m[2]}` });
    }
  }

  return groups;
}
