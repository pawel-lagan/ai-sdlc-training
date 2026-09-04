# Demo validation status

Validated in the authoring environment:

- all expected C++/Go source, test, fixture, prompt, and build-metadata files are present;
- C++ sources contain ASCII-only code for GCC/MSVC source-encoding portability;
- `create-test-plan` and `terse-diagnostic-output` pass the bundled skill frontmatter/scaffold validator;
- Markdown fences and relative links in the workshop guide are balanced/resolvable;
- Demo 08 uses only injected fake transports and `example.invalid` documentation;
- compact-output fallbacks are explicitly labelled as simulations.

Not run in the authoring environment:

- CMake configuration or compilation;
- GCC tests;
- MSVC tests;
- Go formatting, compilation, vet, or tests.

Reason: this local session exposes none of `cmake`, `g++`, `cl`, `msbuild`, or `go`. The facilitator must run the following preflight on the actual workshop machines.

## C++ preflight

Run in each C++ demo directory containing `CMakeLists.txt`:

```text
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

For Visual Studio multi-configuration builds:

```text
cmake -S . -B build
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

Demo 03 has no passing CTest because its executable intentionally returns `1`; build it and run `noisy_ci --mode compare` manually.

## Go preflight

Run in every directory containing `go.mod`:

```text
gofmt -w .
go test ./...
go vet ./...
```

For Demo 03, use `go run ./cmd/noisy-ci --mode compare`; exit code `1` is intentional.
