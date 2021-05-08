set(MODULE_NAME LoggerTests)

set(HEADERS
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_logger.cpp
)

add_executable(${MODULE_NAME} ${SOURCES})


target_link_libraries(
    ${MODULE_NAME}
    PRIVATE 
    gtest_main
    Logger::logger
)

include(GoogleTest)
gtest_discover_tests(${MODULE_NAME})
