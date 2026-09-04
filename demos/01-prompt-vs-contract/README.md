# Demo 01 — Prompt vs specification contract

Goal: compare a minimal planning prompt with a task contract that exposes assumptions before code changes.

Both variants contain the same deployment-gate baseline and behavior. Run the baseline tests, then start two fresh agent conversations. In Run A use:

```text
Add change-risk handling to the deployment gate. Plan first; do not edit files.
```

In Run B use the language-specific `prompts/contract.md`. Compare exact files, cases, assumptions, non-goals, verification commands, and approval boundaries. Implementation is optional.
