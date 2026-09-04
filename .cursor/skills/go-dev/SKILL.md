---
name: go-dev
description: Build, verify, and run Go modules and applications. Use when the repository has go.mod or go.work, or the user asks to compile, test, vet, race-check, or run Go programs; do not use for GCC, MSVC, or other C/C++ toolchain workflows.
---

# Go development

Honor the Go version, module boundaries, build tags, generated-code policy, and commands already declared by the repository and CI. Use repository wrappers (`Makefile`, `task`, scripts) when they own the flow.

## Workflow

1. Inspect `go.mod`, `go.work`, package layout, `cmd/` (or other `package main` entry points), build tags, task runners, CI, and `AGENTS.md`. Record `go version` and `go env GOMOD GOWORK GOOS GOARCH`.
2. Reproduce the current state with the narrowest command: one package, one test, or one main.
3. Implement the smallest change that meets approved acceptance criteria. Prefer the standard library and existing dependencies; adding or upgrading a module is a separate design decision.
4. Format changed Go files with `gofmt` or the repository formatter.
5. **Build.** Compile the affected packages (`go build ./path`) and, for applications, produce a binary with an explicit `-o` path. Treat new compile errors as blockers; do not claim a run succeeded without a successful build.
6. **Verify.** Run focused tests first, then `go test ./...` when repository practice permits. Run `go vet ./...` for code changes. Run `go test -race` for concurrency-sensitive changes on supported platforms. Record any check the environment cannot run.
7. **Run.** Only run a program when the task requires observing runtime behavior. Prefer `go run` for a short local invocation; use the built binary when flags, cwd, or artifacts matter. Capture command, working directory, args, stdout/stderr, and exit status. Do not leave long-lived servers running unless the user asked; if a server is required, start it in the background and stop it after verification.
8. Report Go version, commands, packages built/tested, binary path if any, race/vet results, run evidence, dependency changes, and omitted checks.

## Non-negotiable checks

- Do not edit generated files unless the repository documents the generator and the task requires regeneration.
- Do not use `go mod tidy` as automatic cleanup; run it only when imports or requirements changed, then inspect the diff.
- Preserve cancellation, timeout, and error-wrapping behavior across call boundaries.
- Avoid goroutine leaks: make ownership, shutdown, and channel closing explicit.
- Prefer table-driven tests when several cases express one behavior, but follow local style.
- Never treat `go run` or a manual process start as a substitute for tests.
- Never convert an intended check into a claimed pass. If tests were skipped, say they were skipped.

## Evidence

Every completed build/verify/run reports:

- Go version and `GOOS`/`GOARCH`
- Exact commands and working directory
- Packages or binaries built
- Tests, vet, and race results (or why omitted)
- Run args, exit status, and relevant output when a program was executed
- Module diffs if `go.mod` / `go.sum` changed

Read [references/command-card.md](references/command-card.md) for build, run, test, race, coverage, module, and debugging patterns.
