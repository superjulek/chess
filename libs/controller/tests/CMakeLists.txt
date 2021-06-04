set(MODULE_NAME ControllerTests)

set(HEADERS
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_controller.cpp
)

add_executable(${MODULE_NAME} ${SOURCES})

target_link_libraries(
    ${MODULE_NAME}
   PUBLIC
    gtest_main
    Chess::chess
    Game::game
    Loader::loader
    View::view
    Controller::controller
)

include(GoogleTest)
gtest_discover_tests(${MODULE_NAME})
