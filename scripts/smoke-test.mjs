// Runs a full simulation through the WASM build under Node, so the engine can be
// checked without a browser:  node scripts/smoke-test.mjs [configFile]
import { readFileSync } from "node:fs";
import { fileURLToPath, pathToFileURL } from "node:url";
import path from "node:path";

const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, "..");

// Windows absolute paths are not valid ESM specifiers -- go through file:// URLs.
const wasmModule = pathToFileURL(path.join(root, "public", "wasm", "robotwars.mjs")).href;
const createRobotWars = (await import(wasmModule)).default;

const configFile = process.argv[2] ?? path.join(root, "engine", "10x10.txt");
const config = readFileSync(configFile, "utf8");

const Module = await createRobotWars();
const sim = new Module.Simulation();

if (!sim.init(config, 12345)) {
  console.error("init failed:", sim.error());
  process.exit(1);
}

console.log(`config: ${path.basename(configFile)}`);
let state = JSON.parse(sim.snapshot());
console.log(`${state.rows}x${state.cols}, ${state.robots.length} robots, ${state.totalSteps} steps\n`);
console.log(state.grid.join("\n"));

let turns = 0;
while (sim.step()) {
  turns++;
  state = JSON.parse(sim.snapshot());
  if (state.finished) break;
}

console.log(`\nafter ${turns} turns:\n`);
console.log(state.grid.join("\n"));
console.log("\nlast turn log:\n" + sim.log().trim().split("\n").slice(0, 12).join("\n"));
console.log("\nrobots:");
for (const r of state.robots) {
  console.log(`  ${r.name.padEnd(10)} ${r.type.padEnd(14)} (${r.x},${r.y})  kills=${r.kills} deaths=${r.deaths} alive=${r.alive}`);
}
console.log("queue:", state.queue.join(", ") || "(empty)");
console.log("listSize:", state.listSize, "finished:", state.finished);

sim.delete();
