set(MODULE_NAME GameTests)

set(HEADERS
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_game.cpp
)

add_executable(${MODULE_NAME} ${SOURCES})

target_link_libraries(
    ${MODULE_NAME}
    PRIVATE
    gtest_main
    Chess::chess
    Game::game
)

include(GoogleTest)
gtest_discover_tests(${MODULE_NAME})
