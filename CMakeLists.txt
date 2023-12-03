cmake_minimum_required(VERSION 3.16)
project(vector)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")

set(VecTEST vector_test.cpp vector.h)

add_executable(vector ${VecTEST})

add_custom_target(coverage
        COMMAND vector  # Run tests
        COMMAND lcov --directory . --capture --output-file coverage.info  # Capture coverage data
        COMMAND lcov --remove coverage.info '/usr/*' --output-file coverage.info  # Remove system paths from coverage info
        COMMAND genhtml coverage.info --output-directory coverage_report  # Generate HTML report
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}  # Set working directory
        COMMENT "Generating code coverage report"
)

target_link_libraries(vector ${GTEST_BOTH_LIBRARIES} pthread)

