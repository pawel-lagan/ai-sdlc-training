package retry

import "fmt"

type Decision struct {
	Retry   bool
	DelayMS int
}

func Decide(code string, attempt int) (Decision, error) {
	if attempt < 1 {
		return Decision{}, fmt.Errorf("attempt must be a positive integer")
	}
	retryable := code == "TIMEOUT" || code == "TEMPORARY_UNAVAILABLE"
	if !retryable || attempt >= 3 {
		return Decision{Retry: false, DelayMS: 0}, nil
	}
	return Decision{Retry: true, DelayMS: attempt * 1000}, nil
}
