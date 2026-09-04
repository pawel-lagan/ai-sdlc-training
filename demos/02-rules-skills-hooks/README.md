# Demo 02 — Rule vs Skill vs Hook

Goal: separate stable repository guidance, a reusable test-planning procedure, and deterministic event automation.

1. Run the baseline C++ or Go tests.
2. Inspect `AGENTS.md`; it contains stable, cross-language boundaries only.
3. Invoke `create-test-plan` for `task.md` and the selected variant. It must inspect real code and stop before implementation.
4. Inspect `.cursor/hooks.json.example`. It is deliberately disabled and contains example command.
5. Discuss the required hook stop conditions before supplying a platform-specific implementation.

