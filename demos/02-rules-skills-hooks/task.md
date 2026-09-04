# Task: rate-limited retry policy

Add handling for `RATE_LIMITED`.

- First retry delay: 500 ms.
- Each subsequent retry doubles the previous delay.
- No more than four attempts.
- `AUTH_FAILED` remains non-retryable.
- Preserve the public retry decision shape.
- Stop after plan for human approval before implementation.
