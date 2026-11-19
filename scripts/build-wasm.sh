#!/usr/bin/env bash
# Builds the C++ engine to WebAssembly and drops the artifacts in public/wasm/.
# Requires the emscripten SDK on PATH (source emsdk_env.sh first).
#
#   ./scripts/build-wasm.sh
set -euo pipefail

here="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
root="$(dirname "$here")"
engine="$root/engine"
out="$root/public/wasm"

command -v em++ >/dev/null || { echo "em++ not on PATH -- source emsdk_env.sh first" >&2; exit 1; }
mkdir -p "$out"

# Every engine translation unit except Main.cpp -- the browser owns the turn loop.
sources=(
  "$engine/Robots.cpp" "$engine/Map.cpp" "$engine/RobotList.cpp" "$engine/RobotQueue.cpp"
  "$engine/RoboCop.cpp" "$engine/Terminator.cpp" "$engine/TerminatorRoboCop.cpp"
  "$engine/BlueThunder.cpp" "$engine/Madbot.cpp" "$engine/RoboTank.cpp"
  "$engine/UltimateRobot.cpp" "$engine/Sentinel.cpp" "$engine/PrimeSentinel.cpp"
  "$engine/native/Simulation.cpp" "$engine/native/bindings.cpp"
)

em++ "${sources[@]}" \
  -std=c++17 -O2 \
  --bind \
  -s MODULARIZE=1 \
  -s EXPORT_ES6=1 \
  -s EXPORT_NAME=createRobotWars \
  -s ENVIRONMENT=web,node \
  -s ALLOW_MEMORY_GROWTH=1 \
  -s DISABLE_EXCEPTION_CATCHING=0 \
  -o "$out/robotwars.mjs"

echo "Built: $out/robotwars.mjs + robotwars.wasm"
