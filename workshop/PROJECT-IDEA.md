# Workshop Project: SentinelScan

## Project overview

SentinelScan is a command-line security tool that scans source-code files and reports potential hard-coded credentials.

The tool is intended for local development and CI pipelines. Its output must be deterministic so that implementations written in different programming languages can be compared using the same acceptance tests.

The project is implemented through:

1. Specification and acceptance criteria
2. Technical design
3. Application skeleton
4. Core implementation
5. Automated tests
6. A late change request
7. Specification and implementation update

## Learning objectives

Participants learn how to:

- turn a product idea into testable requirements;
- identify ambiguities before implementation;
- create a simple technical design;
- separate domain logic from file-system and CLI code;
- build a working application incrementally;
- derive tests from acceptance criteria;
- use AI to generate, review, and refine artifacts;
- manage a late requirement without losing consistency between specification, design, code, and tests.

## User story

As a software developer,  
I want to scan a source-code directory for potential hard-coded credentials,  
so that I can detect secrets before committing or deploying the code.

## Command-line interface

```text
sentinelscan scan <directory>
```

Example:

```text
sentinelscan scan ./example-project
```

Initial optional arguments:

```text
--extensions <list>
--max-file-size <bytes>
--quiet
```

Example:

```text
sentinelscan scan ./src --extensions .c,.cpp,.h,.go,.json,.yaml
```

The late change request adds `--fail-on <medium|high|never>` after the initial implementation has reached Review or Release-ready.
