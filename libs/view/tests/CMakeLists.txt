set(MODULE_NAME ViewTests)

set(HEADERS
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_view.cpp
)

add_executable(${MODULE_NAME} ${SOURCES})


target_link_libraries(
    ${MODULE_NAME}
    PRIVATE
    gtest_main
    View::view
    Chess::chess
)

include(GoogleTest)
gtest_discover_tests(${MODULE_NAME})
