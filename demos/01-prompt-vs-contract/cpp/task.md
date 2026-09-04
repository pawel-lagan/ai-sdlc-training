# Task: change risk in the C++ deployment gate

Add `change_risk` with values `low`, `medium`, and `high`.

- Low and medium require no additional approval.
- High in production requires `architecture_approved: true`.
- High outside production follows existing rules.
- Missing or unknown change risk returns a clear input error.
- Preserve the public `GateDecision {allowed, reason}` shape.
- Do not add dependencies, logging, persistence, new abstractions, or pipeline changes.
