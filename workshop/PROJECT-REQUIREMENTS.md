# SentinelScan Project Requirements

## Functional requirements

### FR-001: Directory validation

The application shall verify that the supplied path exists and is a directory. If invalid, it shall write an error to standard error, return exit code `2`, and not start the scan.

### FR-002: Recursive scanning

The application shall recursively scan all regular files under the supplied directory. Directories and files shall be processed in lexicographical order using normalized relative paths to ensure deterministic output.

### FR-003: Symbolic links

The application shall not follow symbolic links. A symbolic link shall not be scanned even when it points to a regular file.

### FR-004: File selection

By default, scan files with these case-insensitive extensions:

```text
.c .cc .cpp .h .hpp .go .json .yaml .yml .env .txt
```

If `--extensions` is supplied, its comma-separated list replaces the defaults.

### FR-005: Maximum file size

Files larger than the configured maximum shall be skipped. The default is `1048576` bytes. Scanning continues after an oversized file is skipped.

### FR-006: Text processing

Process files line by line, support LF and CRLF, report one-based original line numbers, and never include a detected secret value in output.

### FR-007: Secret detection rules

#### SS001: Private key marker

Report `HIGH` when a line contains:

```text
-----BEGIN PRIVATE KEY-----
```

#### SS002: AWS-style access key

Report `HIGH` when a line contains a token that starts with `AKIA`, is followed by exactly 16 uppercase ASCII letters or digits, and is not immediately preceded or followed by an uppercase ASCII letter or digit.

Synthetic example:

```text
AKIA1234567890ABCDEF
```

#### SS003: GitHub-style token

Report `HIGH` when a line contains a token that starts with `ghp_`, is followed by exactly 36 ASCII letters or digits, and is not immediately followed by an ASCII letter or digit. Test data must use synthetic values only.

#### SS004: Generic secret assignment

Report `MEDIUM` when a line assigns one of these case-insensitive identifiers:

```text
password passwd secret api_key token
```

The operator may be `=` or `:` with optional surrounding spaces. The value must be enclosed in single or double quotes, contain at least eight characters, be non-empty, and not contain the closing quote character.

Examples:

```text
password = "synthetic-password"
api_key: 'example-value-123'
TOKEN="not-a-real-token"
```

### FR-008: Multiple findings

If a line matches more than one rule, each matching rule produces a separate finding. The same rule produces at most one finding per line.

### FR-009: Finding order

Sort findings by normalized relative file path, line number, and rule identifier. Output path separators shall always use `/`.

### FR-010: Console output

Each finding uses:

```text
<severity> <rule-id> <relative-path>:<line-number> <message>
```

Examples:

```text
HIGH SS001 keys/example.pem:1 Private key marker detected
MEDIUM SS004 src/config.go:12 Generic secret assignment detected
```

The actual secret value shall never be printed.

### FR-011: Summary

After findings, print:

```text
Scanned: <number>, Skipped: <number>, Findings: <number>
```

### FR-012: Quiet mode

With `--quiet`, individual findings are hidden, the summary remains visible, and exit-code behavior is unchanged.

## Exit codes

```text
0 — scan completed and no findings were detected
1 — scan completed and one or more findings were detected
2 — invalid arguments, invalid configuration, or scan failure
```

A skipped file is not a scan failure.

## Portability

The solution shall run on Linux with GCC, Windows with Microsoft Visual Studio, and any supported platform with Go. Use the language standard library only.

## Security

The application shall never print detected values, execute scanned files, follow symbolic links, or modify scanned files. It shall avoid loading an entire oversized file into memory and handle malformed or unreadable files without crashing.

## Determinism

Given identical directory contents and arguments, every implementation shall produce logically equivalent findings and the same exit code. Execution time and absolute paths shall not appear in output.

## Performance

The workshop release processes files sequentially. Parallel scanning is out of scope.

# Acceptance scenarios

## AC-001: Clean directory

Given only clean source files, scanning prints no finding, reports zero findings, and returns `0`.

## AC-002: Private key marker

Given `-----BEGIN PRIVATE KEY-----`, scanning reports `HIGH SS001` and returns `1`.

## AC-003: Secret redaction

Given:

```text
password = "super-secret-example"
```

Output contains an `SS004` finding and does not contain `super-secret-example`.

## AC-004: Short generic value

Given `password = "short"`, no `SS004` finding is reported for that line.

## AC-005: Deterministic ordering

Given findings in multiple files created in arbitrary order, output is ordered by relative path, line number, and rule identifier.

## AC-006: Unsupported extension

A secret in `image.bin` is not scanned with default options.

## AC-007: Custom extensions

Given a secret in `settings.conf`, invoking `--extensions .conf` scans that file.

## AC-008: Oversized file

A file larger than the configured maximum is skipped, the skipped counter increments, and scanning continues.

## AC-009: CRLF input

Given CRLF input with a secret on line 4, the reported line is `4`.

## AC-010: Quiet mode

Given two findings and `--quiet`, no individual finding is printed, the summary reports two findings, and exit code is `1`.

# Suggested technical design

```text
CLI
 ├── validates arguments
 ├── builds ScanOptions
 └── maps ScanResult to exit code

Scanner
 ├── FileEnumerator
 ├── FileReader
 ├── RuleEngine
 └── FindingCollector

RuleEngine
 ├── PrivateKeyRule
 ├── AwsAccessKeyRule
 ├── GitHubTokenRule
 └── GenericAssignmentRule

Reporter
 ├── sorts findings
 ├── formats paths
 ├── redacts values
 └── prints findings and summary
```

Suggested domain objects:

```text
ScanOptions: rootDirectory, allowedExtensions, maximumFileSize, quiet
Finding: ruleId, severity, relativePath, lineNumber, message
ScanResult: scannedFileCount, skippedFileCount, findings
```

Detection rules should receive text and return findings without reading files or printing output.

# Suggested repository structure

```text
sentinelscan/
├── README.md
├── SPEC.md
├── DESIGN.md
├── CHANGELOG.md
├── src/
│   ├── cli/
│   ├── scanner/
│   ├── rules/
│   └── reporting/
├── tests/
│   ├── unit/
│   ├── integration/
│   └── fixtures/
└── testdata/
    ├── clean/
    ├── findings/
    └── edge-cases/
```

Directory names may follow language conventions, but `SPEC.md`, test data, and expected results are shared.

# Implementation increments

## Increment 1: Walking Skeleton

Implement the executable, `scan` parsing, directory validation, empty scanner, summary, exit codes `0/2`, and one end-to-end smoke test.

Expected empty result:

```text
Scanned: 0, Skipped: 0, Findings: 0
```

## Increment 2: First Vertical Slice

Implement recursive enumeration, extension filtering, `SS001`, finding output, exit code `1`, and unit plus integration tests.

## Increment 3: Complete Detection

Implement `SS002`, `SS003`, `SS004`, deterministic sorting, secret redaction, and CRLF handling.

## Increment 4: Operational Behavior

Implement maximum file size, skipped-file counting, quiet mode, error handling, and the complete acceptance suite.

# Late change request

## CR-001: Severity Threshold

### Business motivation

CI users want to see medium-severity findings but optionally fail the build only for high-severity findings.

### New requirement

Add:

```text
--fail-on <severity>
```

Supported values are `medium`, `high`, and `never`; default is `medium`.

### Updated exit-code behavior

- `--fail-on medium`: return `1` for at least one `MEDIUM` or `HIGH` finding.
- `--fail-on high`: return `1` only for at least one `HIGH` finding.
- `--fail-on never`: a successfully completed scan returns `0`.
- All findings remain reported regardless of threshold.
- Invalid severity returns `2`.

### CR-001 acceptance scenario

Given a directory containing only an `SS004` medium finding, when invoked with `--fail-on high`, the finding is printed, the summary reports one finding, and the exit code is `0`.

This change should expose whether the initial design separated detection, reporting, process outcome, and CLI parsing.

# Cross-team comparison

All teams receive identical specification, fixture files, expected outputs, acceptance scenarios, and exit-code rules. Compare specification compliance, component structure, rule testability, error handling, logging security, CR-001 design impact, and toolchain-specific AI decisions.

GCC and Visual Studio teams should use C++17. A C implementation is possible but requires an explicitly simplified design for memory management and collections.
