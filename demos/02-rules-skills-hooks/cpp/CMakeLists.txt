cmake_minimum_required(VERSION 3.20)
project(demo02_retry_policy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(retry_policy src/retry_policy.cpp)
target_include_directories(retry_policy PUBLIC include)

add_executable(retry_policy_tests tests/retry_policy_test.cpp)
target_link_libraries(retry_policy_tests PRIVATE retry_policy)

enable_testing()
add_test(NAME retry_policy_tests COMMAND retry_policy_tests)
