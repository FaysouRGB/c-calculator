cmake_minimum_required(VERSION 3.10)
project(Calculator)

# Set the C standard.
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add subdirectories for the modules.
add_subdirectory(src/infix)
add_subdirectory(src/queue)
add_subdirectory(src/rpn)
add_subdirectory(src/stack)
add_subdirectory(src/utilities)

# Add the main executable.
add_executable(calculator src/main.c)

# Link the modules with the main executable.
target_link_libraries(calculator infix queue rpn stack utilities)

# Add a custom target to build and run the tests.
add_custom_target(run_tests
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target calculator
    COMMAND bash ${CMAKE_SOURCE_DIR}/tests/testsuite.sh
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Building the project and running the test suite"
)

# Make 'run_tests' depend on 'main' to ensure the build happens first.
add_dependencies(run_tests calculator)
