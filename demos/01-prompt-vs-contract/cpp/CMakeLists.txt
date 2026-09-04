cmake_minimum_required(VERSION 3.20)
project(demo01_deployment_gate LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(deployment_gate src/deployment_gate.cpp)
target_include_directories(deployment_gate PUBLIC include)

add_executable(deployment_gate_tests tests/deployment_gate_test.cpp)
target_link_libraries(deployment_gate_tests PRIVATE deployment_gate)

enable_testing()
add_test(NAME deployment_gate_tests COMMAND deployment_gate_tests)
