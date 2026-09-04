package retry

import "testing"

func TestDecideBaseline(t *testing.T) {
	tests := []struct {
		name    string
		code    string
		attempt int
		want    Decision
	}{
		{"timeout retries", "TIMEOUT", 2, Decision{true, 2000}},
		{"third attempt stops", "TIMEOUT", 3, Decision{false, 0}},
		{"auth never retries", "AUTH_FAILED", 1, Decision{false, 0}},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			got, err := Decide(tt.code, tt.attempt)
			if err != nil { t.Fatalf("Decide() error = %v", err) }
			if got != tt.want { t.Fatalf("Decide() = %#v, want %#v", got, tt.want) }
		})
	}
}

func TestDecideRejectsInvalidAttempt(t *testing.T) {
	if _, err := Decide("TIMEOUT", 0); err == nil {
		t.Fatal("expected invalid attempt error")
	}
}
