export interface RobotState {
  name: string;
  type: string;
  initial: string;
  /** row index into the battlefield (matches the C++ `X`) */
  x: number;
  /** column index into the battlefield (matches the C++ `Y`) */
  y: number;
  kills: number;
  deaths: number;
  alive: boolean;
}

export interface SimState {
  turn: number;
  totalSteps: number;
  finished: boolean;
  ready: boolean;
  rows: number;
  cols: number;
  /** one string per row, '.' for an empty cell */
  grid: string[];
  robots: RobotState[];
  queue: string[];
  listSize: number;
  error: string;
}

export type TurnEventKind = "move" | "fire" | "kill" | "step" | "revive";

export interface TurnEvent {
  kind: TurnEventKind;
  /** initial of the robot that acted */
  actor: string;
  x: number;
  y: number;
  /** initial of the robot that was destroyed, for kill/step events */
  victim?: string;
}
