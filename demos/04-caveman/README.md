# Demo 04 — Terse diagnostics without evidence loss

Goal: compare normal diagnostic prose with a local skill that removes padding while preserving cause, evidence, safe action, verification, and uncertainty.

1. Select `incident.log`.
2. Start a fresh conversation and add 'Do not use any skill' + send `prompt.md`.
3. Start another fresh conversation, invoke `caveman-output` skill, and send the same prompt.
4. Compare both with the relevant saved fixtures.
5. Grade six fields: cause, exact evidence, safe action, verification, uncertainty, and no invented facts.

The saved fixtures are deterministic fallbacks. A shorter answer fails if it removes a required field.
