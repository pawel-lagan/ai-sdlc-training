# Demo project instructions

- Use exactly one stack skill for implementation and verification: `gcc-dev`, `go-dev`, or `mscpp-dev`.
- Preserve public result shapes and existing behavior unless `task.md` explicitly changes them.
- Keep retry decisions pure; do not add sleep, I/O, logging, or network calls to domain code.
- Use behavior-focused test names and run the narrowest affected test before the complete suite.
- Do not edit production code while creating a test plan.
- Do not enable the example stop hook without an explicit human-approved command.
- Show test output

Language-specific compiler, runtime, and test-runner decisions belong in the selected stack skill, not this shared file.
