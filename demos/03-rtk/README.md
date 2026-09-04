# Demo 03 — Raw vs compact terminal evidence

Goal: show that command output can be reduced before entering agent context while preserving the diagnostic signal.

Both programs generate the same deterministic simulated CI result: 120 passes and one failure. They support:

```text
--mode raw
--mode compact
--mode compare
```

All modes intentionally return exit code `1`. `compare` reports lines and bytes, then prints the compact failure signal. This is not an RTK benchmark and makes no claim about complete-session token cost.

C++:

```text
cmake -S cpp -B cpp/build
cmake --build cpp/build
cpp/build/noisy_ci --mode compare
```

Go:

```text
cd go
go run ./cmd/noisy-ci --mode compare
```

Fallback: compare `fixtures/raw-output-excerpt.txt` and `fixtures/compact-output.txt`; require the test name, expected/actual values, source location, summary, and failure status to survive.
