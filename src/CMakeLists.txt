set(MODULE_NAME ChessGame)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/config.h
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/chess_game.cpp
)

add_executable(${MODULE_NAME} ${SOURCES})

target_link_libraries(
    ${MODULE_NAME}
    PRIVATE
    Logger::logger
)
