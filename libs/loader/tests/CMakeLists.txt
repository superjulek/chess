set(MODULE_NAME LoaderTests)

set(HEADERS
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_loader.cpp
)

add_executable(${MODULE_NAME} ${SOURCES})

target_link_libraries(
    ${MODULE_NAME}
    PRIVATE
    gtest_main
    Chess::chess
    Game::game
    Loader::loader
)

include(GoogleTest)
gtest_discover_tests(${MODULE_NAME})
