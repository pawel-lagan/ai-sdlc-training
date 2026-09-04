package deploymentgate

import "testing"

func TestEvaluateBaseline(t *testing.T) {
	tests := []struct {
		name  string
		input Input
		want  Decision
	}{
		{"staging ready", Input{"staging", "passed", false, 0, "low", false}, Decision{true, "ready"}},
		{"production low risk", Input{"production", "passed", false, 0, "low", false}, Decision{false, "release-not-approved"}},
		{"production medium risk", Input{"production", "passed", false, 0, "medium", false}, Decision{false, "release-not-approved"}},
		{"production high risk release not approved", Input{"production", "passed", false, 0, "high", false}, Decision{false, "release-not-approved"}},
		{"production high risk architecture not approved", Input{"production", "passed", true, 0, "high", false}, Decision{false, "architecture-not-approved"}},
		{"production high risk approved", Input{"production", "passed", true, 0, "high", true}, Decision{true, "ready"}},
		{"staging high risk", Input{"staging", "passed", false, 0, "high", false}, Decision{true, "ready"}},
		{"active incident", Input{"staging", "passed", true, 1, "low", false}, Decision{false, "active-incident"}},
		{"failed tests", Input{"production", "failed", true, 0, "low", false}, Decision{false, "tests-not-passed"}},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			got, err := Evaluate(tt.input)
			if err != nil {
				t.Fatalf("Evaluate() error = %v", err)
			}
			if got != tt.want {
				t.Fatalf("Evaluate() = %#v, want %#v", got, tt.want)
			}
		})
	}
}

func TestEvaluateRejectsInvalidInput(t *testing.T) {
	if _, err := Evaluate(Input{"prod", "passed", true, 0, "low", false}); err == nil {
		t.Fatal("expected invalid environment error")
	}
	if _, err := Evaluate(Input{"production", "passed", true, 0, "critical", false}); err == nil {
		t.Fatal("expected invalid change risk error")
	}
	if _, err := Evaluate(Input{"production", "passed", true, 0, "", false}); err == nil {
		t.Fatal("expected invalid change risk error")
	}
}
