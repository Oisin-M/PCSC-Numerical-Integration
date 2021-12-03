cmake_minimum_required (VERSION 3.1)
project (Project5)

set(CMAKE_CXX_STANDARD 14)

include_directories(eigen)
add_executable(integration integration.cpp AbstractIntegrationMethod.cpp MidpointFormula.cpp TrapezoidalRule.cpp SimpsonsRule.cpp)
add_executable(readfile readfile.cpp)

