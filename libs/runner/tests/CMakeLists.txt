set(MODULE_NAME RunnerTests)

set(HEADERS
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_runner.cpp
)

add_executable(${MODULE_NAME} ${SOURCES})


target_link_libraries(
    ${MODULE_NAME}
   PUBLIC
    gtest_main
    Runner::runner
)

include(GoogleTest)
gtest_discover_tests(${MODULE_NAME})
