// The same .txt configs the desktop program reads, inlined so the page can offer
// them as presets and let you edit one before starting a run.

export const PRESETS: Record<string, string> = {
  "10 x 10": `M by N : 10 10
steps: 30
robots: 7
Madbot Mold 3 6
RoboTank Orion 9 1
Terminator T-1000 4 random
BlueThunder Bast random random
Sentinel Seneca 5 5
RoboCop Ra-One 1 1
TerminatorRoboCop Chrono 8 8`,

  "20 x 20": `M by N : 20 20
steps: 30
robots: 9
Madbot Mold 3 6
RoboTank Orion 12 1
Terminator T-1000 15 random
BlueThunder Bast random random
Sentinel Seneca 5 5
RoboCop Ra-One 10 10
TerminatorRoboCop Chrono 8 8
UltimateRobot Ultrabot random random
PrimeSentinel Nimrod 7 random`,

  "30 x 30": `M by N : 30 30
steps: 30
robots: 18
Madbot Mold 3 6
RoboTank Orion 12 1
Terminator T-1000 15 random
BlueThunder Bast random random
Sentinel Seneca 5 5
RoboCop Ra-One 10 10
TerminatorRoboCop Chrono 8 8
UltimateRobot Ultrabot random random
PrimeSentinel Nimrod 7 random
Madbot master 23 26
RoboTank paxion 26 11
Terminator t-huan 25 random
BlueThunder basthion random random
Sentinel sinister random 25
RoboCop radbot 20 20
TerminatorRoboCop chton 28 28
UltimateRobot Harbinger random random
PrimeSentinel nexus 27 random`,
};

export const DEFAULT_PRESET = "20 x 20";

// Colour per robot type, so the board reads at a glance.
export const TYPE_COLOURS: Record<string, string> = {
  RoboCop: "#f97316",
  Terminator: "#ef4444",
  "T-RoboCop": "#facc15",
  BlueThunder: "#a3e635",
  Madbot: "#f472b6",
  RoboTank: "#cbd5e1",
  UltimateRobot: "#a855f7",
  Sentinel: "#10b981",
  PrimeSentinel: "#e7e5e4",
};

export function colourFor(type: string): string {
  return TYPE_COLOURS[type] ?? "#9ca3af";
}
