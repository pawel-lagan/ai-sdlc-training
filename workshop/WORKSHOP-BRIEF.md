# SentinelScan — SDLC in Action

## Mission

Implement SentinelScan through the repository's governed SDLC. The goal is not maximum generated code. The goal is a traceable, portable, secure implementation whose observable behavior is supported by reproducible evidence.

This `workshop/` directory must be copied into the root of the disposable team repository created from the workshop `starter-repo/`. Confirm that the same project root also contains `AGENTS.md`, the three stack skills, the SDLC orchestrator adapters, and the specification templates before starting.

## Team assignments

- Team A: C++17, Linux, GCC, `gcc-dev`
- Team B: C++17, Windows, Visual Studio/MSVC, `mscpp-dev`
- Team C: Go, repository-declared Go version, `go-dev`

All teams use the same requirement identifiers, synthetic test data, normalized expected output, and exit-code contract.

## Rules of engagement

1. Start with Intake and Specify. Do not edit product code before human specification approval.
2. Preserve `FR-*`, `AC-*`, and `CR-*` identifiers in plans, tasks, tests, and evidence.
3. Let repository evidence select exactly one development skill.
4. Implement in vertical increments and verify each increment before widening scope.
5. Never print or store a detected secret value in a finding or diagnostic.
6. Use synthetic test values only. Do not scan participant home directories or production repositories.
7. Do not follow symbolic links, execute scanned files, access the network, or modify scanned content.
8. Record failures, blocked checks, and unrun checks honestly.
9. Stop at Release-ready. Do not push, merge, publish, or deploy without separate authorization.

## Required lifecycle artifacts

```text
specs/changes/sentinelscan-v1/
├── spec.md
├── plan.md
├── tasks.md
└── evidence.md
```

Create a second change directory for the late request:

```text
specs/changes/sentinelscan-fail-threshold/
├── spec.md
├── plan.md
├── tasks.md
└── evidence.md
```

## Checkpoints

### Gate 1 — Specification approved

- Observable behavior and non-goals are explicit.
- Cross-platform ambiguities have an owner and resolution.
- Acceptance scenarios map to proposed evidence.
- Approver, date, and revision are recorded.

### Gate 2 — Design and plan ready

- CLI, scanning, detection, reporting, and exit policy are separated.
- Every task maps to requirements and verification.
- Focused checks precede broader checks.
- The stack-specific environment is identified.

### Gate 3 — Initial release reviewed

- Implemented increments have real evidence.
- Redaction has a negative assertion for stdout and stderr.
- Deterministic ordering and normalized paths are verified.
- Missing platform checks and residual risks are explicit.

### Gate 4 — Late change approved

- CR-001 updates specification and acceptance criteria before code.
- The impact map identifies CLI, options, reporting, exit policy, tests, and help text.
- Previous approval is not reused for the new scope.

### Gate 5 — Release-ready

- `--fail-on` changes process outcome without hiding findings.
- Default, `high`, `never`, invalid input, quiet mode, and existing error behavior have regression evidence.
- Cross-team conformance findings are resolved or recorded.

## Starting prompt

```text
Use the sdlc_orchestrator for SentinelScan v1.
Read capstone/PROJECT-IDEA.md and capstone/PROJECT-REQUIREMENTS.md.
Create Intake and Specify artifacts only. Preserve requirement and acceptance identifiers.
List ambiguities that affect observable behavior, portability, security, or verification.
Select the stack skill from repository evidence. Stop at the human specification gate.
```

## Definition of done

The team is done only when its declared scope is implemented, every in-scope acceptance scenario has Pass, Fail, Blocked, or Not run evidence, the diff has been reviewed against the approved specification, and the orchestrator stops at Release-ready.
