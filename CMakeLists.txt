cmake_minimum_required (VERSION 3.1)
project (Project5)

set(CMAKE_CXX_STANDARD 14)

include_directories(eigen)
include_directories(googletest/googletest/googletest/include)
add_executable(integration integration.cpp AbstractReader.cpp TxtReader.cpp AbstractIntegrationMethod.cpp MidpointFormula.cpp TrapezoidalRule.cpp SimpsonsRule.cpp)
add_executable(readfile readfile.cpp)
add_executable(Test Test.cpp)
add_executable(offreadfile offreadfile.cpp)

