---
name: gcc-dev
description: Build, test, debug, and review C or C++ projects that use GCC on Linux. Use for gcc, g++, Make, CMake, Ninja, GDB, sanitizers, Valgrind, or Linux-native compiler diagnostics; do not use for MSVC-only builds or Go modules.
---

# GCC development

Preserve the repository's existing build system and language standard. Inspect `Makefile`, `CMakeLists.txt`, presets, CI, and `AGENTS.md` before choosing commands. Do not introduce a new build system or raise the C/C++ standard unless the approved specification requires it.

## Workflow

1. Identify whether the target is C or C++, the build entry point, compiler version, build type, and test runner.
2. Reproduce the current state with the narrowest build or test that exercises the requested behavior.
3. Implement the smallest change that satisfies the approved acceptance criteria. Preserve ABI/API compatibility unless the specification explicitly changes it.
4. Compile with the repository's normal warnings. Treat new warnings as regressions; do not hide them with broad suppressions.
5. Run focused tests first, then the documented broader suite. For memory, undefined-behavior, or concurrency-sensitive changes, use the appropriate sanitizer build when available.
6. Report exact commands, compiler identity, tests run, and any validation not performed.

## Safety and portability

- Use the repository driver: `gcc` for C and normally `g++` for C++.
- Never mix build directories, architectures, standard libraries, or incompatible compile options in one artifact tree.
- Do not hand-edit generated build files or vendored dependencies.
- Prefer reproducible commands over machine-specific absolute paths.
- Reduce noisy diagnostics to the first actionable compiler error before changing code.

Read [references/command-card.md](references/command-card.md) when selecting direct GCC, CMake, sanitizer, debugger, or Valgrind commands.
