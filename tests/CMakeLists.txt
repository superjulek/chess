set(MODULE_NAME UTests)

set(HEADERS
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_many.cpp
)

add_executable(${MODULE_NAME} ${SOURCES})


target_link_libraries(
    ${MODULE_NAME}
   PUBLIC 
    gtest_main
    Logger::logger
)

include(GoogleTest)
gtest_discover_tests(${MODULE_NAME})
