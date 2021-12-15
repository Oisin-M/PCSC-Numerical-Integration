cmake_minimum_required (VERSION 3.1)
project (Project5)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest/googletest)

include_directories(eigen)

add_executable(integration integration.cpp AbstractReader.cpp TxtReader.cpp AbstractIntegrationMethod.cpp MidpointFormula.cpp TrapezoidalRule.cpp SimpsonsRule.cpp)

add_executable(Tests tests/Tests.cpp AbstractReader.cpp MidpointFormula.cpp AbstractIntegrationMethod.cpp)
target_link_libraries(Tests gtest_main gtest)


