#include "deployment_gate.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

using demo01::ChangeRisk;
using demo01::DeploymentInput;
using demo01::Environment;
using demo01::GateDecision;
using demo01::TestStatus;

namespace {

void require(bool condition, const std::string& message) {
    if (!condition) throw std::runtime_error(message);
}

void require_decision(const GateDecision& actual, bool allowed, const std::string& reason) {
    require(actual.allowed == allowed, "unexpected allowed value");
    require(actual.reason == reason, "unexpected reason: " + actual.reason);
}

}  // namespace

int main() {
    try {
        require_decision(demo01::evaluate_deployment(
            {Environment::Staging, TestStatus::Passed, false, 0, ChangeRisk::Low}), true, "ready");
        require_decision(demo01::evaluate_deployment(
            {Environment::Production, TestStatus::Passed, false, 0, ChangeRisk::Low}), true, "ready");
        require_decision(demo01::evaluate_deployment(
            {Environment::Production, TestStatus::Passed, false, 0, ChangeRisk::Medium}), true, "ready");
        require_decision(demo01::evaluate_deployment(
            {Environment::Production, TestStatus::Passed, false, 0, ChangeRisk::High}), false, "release-not-approved");
        require_decision(demo01::evaluate_deployment(
            {Environment::Staging, TestStatus::Passed, true, 1, ChangeRisk::Low}), false, "active-incident");
        require_decision(demo01::evaluate_deployment(
            {Environment::Production, TestStatus::Failed, true, 0, ChangeRisk::Low}), false, "tests-not-passed");
        require_decision(demo01::evaluate_deployment(
            {Environment::Staging, TestStatus::Passed, false, 0, ChangeRisk::High}), true, "ready");
        require_decision(demo01::evaluate_deployment(
            {Environment::Production, TestStatus::Passed, true, 0, ChangeRisk::High}), true, "ready");

        bool rejected = false;
        try {
            (void)demo01::evaluate_deployment(
                {Environment::Development, TestStatus::Passed, true, -1, ChangeRisk::Low});
        } catch (const std::invalid_argument&) {
            rejected = true;
        }
        require(rejected, "negative incident count must be rejected");
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
    std::cout << "PASS: deployment gate baseline\n";
    return 0;
}
