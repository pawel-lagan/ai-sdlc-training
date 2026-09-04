# Go command card

Use repository wrappers when present. These commands are selection patterns.

```bash
go version
go env GOMOD GOWORK GOOS GOARCH
go list ./...
gofmt -w path/to/changed.go
go test ./path/to/package -run '^TestName$/^case$' -count=1
go test ./path/to/package -count=1
go test ./...
go vet ./...
go test -race ./...
go test ./... -coverprofile=coverage.out
go tool cover -func=coverage.out
go test ./path/to/package -bench . -benchmem
go mod tidy
go mod verify
```

For debugger work, prefer the repository's documented Delve flow. A common local pattern is `dlv test ./path/to/package -- -test.run TestName`.

Record environment-dependent exclusions, such as race detector support, CGO requirements, integration credentials, or platform build tags.
