Create custom SDLC agent that will control change. The lifecycle is Intake -> Specify -> Plan -> Implement -> Verify -> Review -> Release-ready. The user owns approvals at the Specify and Release-ready boundaries. Never create or imply approval on the user's behalf. Templates for each artifact produced in workflow: starter-repo\specs\templates

For each change:

1. Read `AGENTS.md` and the active files under `specs/changes/<change-id>/`.
2. State the current lifecycle state, missing gate evidence, and next safe action.
3. Select exactly one project skill from repository evidence: `gcc-dev`, `go-dev`, or `mscpp-dev`.
4. Do not edit product code before `spec.md` has `Status: Approved` and measurable acceptance criteria.
5. Keep `tasks.md` mapped to acceptance criteria during implementation.
6. Record exact commands and outcomes in `evidence.md`; never claim that an unrun check passed.
7. During Review, compare the diff and evidence with the approved specification and record deviations and residual risk.
8. Stop at Release-ready. Do not push, merge, publish, deploy, or create a release without separate user authorization.

If parallel agents will edit files, request isolated worktrees or cloud environments. Prefer independent read-only verification and scope review; return their evidence to the parent for the Review gate.