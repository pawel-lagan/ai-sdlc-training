#pragma once

#include <string>

namespace demo01 {

enum class Environment { Development, Staging, Production };
enum class TestStatus { Passed, Failed, Skipped };
enum class ChangeRisk { Low, Medium, High };

struct DeploymentInput {
    Environment environment;
    TestStatus test_status;
    bool release_approved;
    int active_incidents{0};
    ChangeRisk change_risk{ChangeRisk::Low};
};

struct GateDecision {
    bool allowed;
    std::string reason;
};

GateDecision evaluate_deployment(const DeploymentInput& input);

}  // namespace demo01
