---
name: mscpp-dev
description: Build, test, debug, and review native C++ projects with Visual Studio and Microsoft MSVC tools on Windows. Use for .sln, .vcxproj, MSBuild, cl.exe, CMake with Visual Studio generators, CTest, Windows SDK, or MSVC diagnostics; do not use for GCC/Linux or Go workflows.
---

# Microsoft C++ development

Work from a Visual Studio Developer PowerShell or Developer Command Prompt when command-line tools are not already configured. Preserve the solution's platform toolset, Windows SDK, runtime library, architecture, configuration, and language standard.

## Workflow

1. Inspect `.sln`, `.vcxproj`, `CMakeLists.txt`, `CMakePresets.json`, CI, test adapters, and `AGENTS.md`. Determine whether MSBuild or CMake is authoritative.
2. Record the selected configuration and platform, such as `Debug|x64`, and reproduce the issue with the narrowest build or test.
3. Implement the smallest change that satisfies the approved acceptance criteria. Preserve ABI, calling convention, character-set, and runtime-library compatibility unless the specification explicitly changes them.
4. Build with normal project warnings. Treat new warnings as regressions and do not add broad suppressions.
5. Run focused tests, then the documented suite. Use AddressSanitizer or native diagnostics when relevant and supported by the selected toolset.
6. Report the exact shell, command, solution/project or preset, configuration, platform, MSVC toolset, tests, and omitted checks.

## Safety and reproducibility

- Do not mix `Win32`, `x64`, and `ARM64` artifacts or `Debug` and `Release` output trees.
- Do not mix `/MD`, `/MDd`, `/MT`, and `/MTd` across linked components without an explicit compatibility decision.
- Never hand-edit generated Visual Studio files when CMake or another generator owns them.
- Quote Windows paths and avoid assuming Visual Studio is installed in one fixed directory.
- Do not translate GCC flags mechanically; select the MSVC equivalent and confirm support for the installed toolset.

Read [references/command-card.md](references/command-card.md) for MSBuild, CMake, CTest, VsDevCmd, and direct `cl` patterns.
