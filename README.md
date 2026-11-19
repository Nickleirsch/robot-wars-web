# Robot Wars

A robot battle simulator written in C++, with a web front-end that runs the same engine in the browser via WebAssembly.

- **Console program:** `engine/` (compile `engine/*.cpp`, which includes `Main.cpp`)
- **Web app:** the Next.js site at the repo root, deployable to Vercel as a static site

## Layout

```
engine/                     C++ simulation (shared by both front-ends)
  *.cpp, *.h                robots, map, robot list/queue, Main.cpp (console game)
  10x10.txt, 20x20.txt, 30x30.txt, battlefield.txt   battlefield configs
  native/                   Simulation driver + embind bindings used only by the web build
app/, components/, lib/     Next.js / React UI
public/wasm/                compiled engine (robotwars.mjs + robotwars.wasm), committed
scripts/                    build-wasm.ps1 / build-wasm.sh, smoke-test.mjs
```

## Console program

Build from the `engine/` folder with any C++17 compiler, for example:

```
g++ -std=c++17 *.cpp -o robotwars
./robotwars
```

## Web app

```
npm install
npm run dev        # http://localhost:3000
```

The browser loads `public/wasm/robotwars.mjs` at runtime. Vercel does not compile C++, so the
WebAssembly build output is committed to the repo.

### Rebuilding the WebAssembly engine

Requires the [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html).

- Windows: `powershell -ExecutionPolicy Bypass -File scripts\build-wasm.ps1`
- macOS / Linux: `./scripts/build-wasm.sh` (after sourcing `emsdk_env.sh`)

Then check the engine under Node: `node scripts/smoke-test.mjs`

## Deploying to Vercel

Import the repository in Vercel. The Next.js app is at the repo root, so the default settings work
(framework: Next.js, build command: `next build`).
