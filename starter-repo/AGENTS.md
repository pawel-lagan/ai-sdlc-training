# Repository instructions

## Delivery model

This repository uses specification-driven development. Active changes live under `specs/changes/<change-id>/` and move through: Intake, Specify, Plan, Implement, Verify, Review, Release-ready.

- Do not modify product code until `spec.md` contains `Status: Approved` and measurable acceptance criteria.
- Use the `sdlc_orchestrator` custom agent to coordinate a change.
- Use exactly one stack skill for implementation and verification: `gcc-dev`, `go-dev`, or `mscpp-dev`.
- Record actual commands and results in `evidence.md`; never convert an intended check into a claimed result.
- A human approves the specification and authorizes any merge, push, deployment, publication, or release.

## Repository care

- Preserve unrelated user changes.
- Prefer focused verification before the broad suite.
- Treat generated files, vendored code, dependency changes, public API/ABI changes, and security-sensitive behavior as explicit scope decisions.
- Keep secrets out of prompts, specs, logs, and committed files.
