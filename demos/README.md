# AI SDLC workshop demos

These installation-free training projects provide C++17 and Go variants of Demos 01–04 and 08. Every live path has a deterministic fallback. Open one language directory as a disposable project; do not run demos against production repositories or real credentials.

| Demo | C++ | Go | Primary lesson |
|---|---|---|---|
| 01 — Prompt vs contract | Buildable baseline and tests | Buildable baseline and tests | Decision ownership before implementation |
| 02 — Rule vs Skill vs Hook | Retry policy and tests | Retry policy and tests | Put responsibility in the right mechanism |
| 03 — Terminal evidence | Raw/compact output generator | Raw/compact output generator | Reduce noise without losing failure signal |
| 04 — Terse diagnostics | Static compiler/linker incident | Static race incident | Preserve evidence while shortening responses |
| 08 — Prompt injection | Safe client over fake transport | Safe client over fake transport | Treat external content as data, not authority |

## C++ prerequisites

- CMake 3.20+
- A C++17 compiler: GCC on Linux or MSVC in a Visual Studio developer environment

Typical flow from a C++ variant directory:

```text
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

For multi-configuration generators, add `--config Debug` to build and test commands.

## Go prerequisites

Use the Go version accepted by the participant repository. From a Go variant directory:

```text
go test ./...
```

## Safety

- All token values are synthetic.
- Demo 08 uses `example.invalid` and fake transports only.
- Demo 08 must not trigger terminal, secret, or network access.
- Static compact output is labelled as simulated and is not an RTK benchmark.
