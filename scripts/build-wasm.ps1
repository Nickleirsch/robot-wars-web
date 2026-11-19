# Builds the C++ engine to WebAssembly and drops the artifacts in public/wasm/.
# Requires the emscripten SDK. Point $env:EMSDK at your install if it is not the default.
#
#   powershell -ExecutionPolicy Bypass -File scripts\build-wasm.ps1

$ErrorActionPreference = "Stop"

$root   = Split-Path -Parent $PSScriptRoot          # repo root
$engine = Join-Path $root "engine"
$outDir = Join-Path $root "public\wasm"

$emsdk = if ($env:EMSDK) { $env:EMSDK } else { Join-Path $env:USERPROFILE "emsdk" }
$emsdkEnv = Join-Path $emsdk "emsdk_env.ps1"
if (-not (Test-Path $emsdkEnv)) {
    throw "emsdk not found at $emsdk. Install it, or set `$env:EMSDK to your install path."
}
& $emsdkEnv | Out-Null

if (-not (Test-Path $outDir)) { New-Item -ItemType Directory -Force $outDir | Out-Null }

# Every engine translation unit except Main.cpp -- the browser owns the turn loop.
$sources = @(
    "Robots.cpp", "Map.cpp", "RobotList.cpp", "RobotQueue.cpp",
    "RoboCop.cpp", "Terminator.cpp", "TerminatorRoboCop.cpp",
    "BlueThunder.cpp", "Madbot.cpp", "RoboTank.cpp",
    "UltimateRobot.cpp", "Sentinel.cpp", "PrimeSentinel.cpp"
) | ForEach-Object { Join-Path $engine $_ }

$sources += (Join-Path $engine "native\Simulation.cpp")
$sources += (Join-Path $engine "native\bindings.cpp")

# emsdk 6.x ships em++.exe; older releases ship em++.bat
$emcc = @("upstream\emscripten\em++.exe", "upstream\emscripten\em++.bat") |
    ForEach-Object { Join-Path $emsdk $_ } |
    Where-Object { Test-Path $_ } |
    Select-Object -First 1
if (-not $emcc) { throw "Could not find em++ under $emsdk" }

& $emcc @sources `
    -std=c++17 -O2 `
    --bind `
    -s MODULARIZE=1 `
    -s EXPORT_ES6=1 `
    -s EXPORT_NAME=createRobotWars `
    -s ENVIRONMENT=web,node `
    -s ALLOW_MEMORY_GROWTH=1 `
    -s DISABLE_EXCEPTION_CATCHING=0 `
    -o (Join-Path $outDir "robotwars.mjs")

if ($LASTEXITCODE -ne 0) { throw "em++ failed with exit code $LASTEXITCODE" }

Write-Host "Built:" (Join-Path $outDir "robotwars.mjs") "+ robotwars.wasm"
