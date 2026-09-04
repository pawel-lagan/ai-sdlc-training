#include "retry_policy.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
void require(bool condition, const std::string& message) {
    if (!condition) throw std::runtime_error(message);
}
}

int main() {
    using demo02::FailureCode;
    try {
        const auto retry = demo02::decide_retry(FailureCode::Timeout, 2);
        require(retry.retry && retry.delay_ms == 2000, "timeout attempt 2 should retry after 2000 ms");

        const auto stop = demo02::decide_retry(FailureCode::Timeout, 3);
        require(!stop.retry && stop.delay_ms == 0, "timeout attempt 3 should stop");

        const auto auth = demo02::decide_retry(FailureCode::AuthFailed, 1);
        require(!auth.retry && auth.delay_ms == 0, "auth failure must not retry");

        bool rejected = false;
        try { (void)demo02::decide_retry(FailureCode::Timeout, 0); }
        catch (const std::invalid_argument&) { rejected = true; }
        require(rejected, "attempt 0 must be rejected");
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
    std::cout << "PASS: retry policy baseline\n";
    return 0;
}
