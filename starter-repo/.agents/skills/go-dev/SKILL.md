---
name: go-dev
description: Build, test, debug, benchmark, and review Go modules. Use for go.mod, go.work, gofmt, go test, go vet, race detection, modules, build tags, or Go tooling; do not use for C/C++ compiler workflows.
---

# Go development

Honor the Go version, module boundaries, build tags, generated-code policy, and commands already declared by the repository and CI.

## Workflow

1. Inspect `go.mod`, `go.work`, package layout, build tags, task runners, CI, and `AGENTS.md`.
2. Reproduce the target behavior with the narrowest package or test command.
3. Implement the smallest change that meets the approved acceptance criteria. Prefer the standard library and existing dependencies; adding or upgrading a module is a separate design decision.
4. Format changed Go files with `gofmt` or the repository formatter.
5. Run focused tests, then `go test ./...` when repository practice permits. Run `go vet ./...` for code changes and `go test -race` for concurrency-sensitive changes on supported platforms.
6. Report commands, Go version, packages tested, race/vet results, dependency changes, and omitted checks.

## Non-negotiable checks

- Do not edit generated files unless the repository documents the generator and the task requires regeneration.
- Do not use `go mod tidy` as automatic cleanup; run it only when imports or requirements changed, then inspect the diff.
- Preserve cancellation, timeout, and error-wrapping behavior across call boundaries.
- Avoid goroutine leaks: make ownership, shutdown, and channel closing explicit.
- Prefer table-driven tests when several cases express one behavior, but follow local style.

Read [references/command-card.md](references/command-card.md) for focused test, race, benchmark, coverage, module, and debugging patterns.
