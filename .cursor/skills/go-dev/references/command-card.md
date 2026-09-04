# Go command card

Use repository wrappers when present. These commands are selection patterns.

## Discover

```bash
go version
go env GOMOD GOWORK GOOS GOARCH
go list ./...
go list -f '{{if eq .Name "main"}}{{.ImportPath}}{{end}}' ./...
```

## Build

```bash
go build ./path/to/package
go build -o bin/app ./path/to/main
go build ./...
```

On Windows, use an explicit output name such as `bin/app.exe`. Do not mix `GOOS`/`GOARCH` cross-compile artifacts into the same verification claim as a native run.

## Verify

```bash
gofmt -w path/to/changed.go
go test ./path/to/package -run '^TestName$/^case$' -count=1
go test ./path/to/package -count=1
go test ./...
go vet ./...
go test -race ./...
go test ./... -coverprofile=coverage.out
go tool cover -func=coverage.out
go test ./path/to/package -bench . -benchmem
go mod verify
```

Race detector support is platform-dependent. If `-race` fails to compile or link, record that omission; do not imply the suite was race-clean.

## Run

```bash
go run ./path/to/main --flag value
go run . --flag value
./bin/app --flag value
```

Use `-count=1` on tests when cache-hit results would hide a flake. For programs that listen on a port, bind to localhost, use a free port, exercise one request, then stop the process.

## Modules

```bash
go mod tidy
go get example.com/module@vX.Y.Z
```

Run `go mod tidy` only after import or requirement changes. Inspect `go.mod` and `go.sum` before committing.

## Debug

Prefer the repository's documented Delve flow. A common local pattern:

```bash
dlv test ./path/to/package -- -test.run TestName
dlv exec ./bin/app -- --flag value
```
