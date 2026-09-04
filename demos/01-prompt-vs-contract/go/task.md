# Task: change risk in the Go deployment gate

Add `ChangeRisk` with values `low`, `medium`, and `high`, plus `ArchitectureApproved`.

- Low and medium require no additional approval.
- High in production requires architecture approval.
- High outside production follows existing rules.
- Missing or unknown risk returns a clear input error.
- Preserve the public `Decision {Allowed, Reason}` shape.
- Do not add dependencies, logging, persistence, or unrelated abstractions.
