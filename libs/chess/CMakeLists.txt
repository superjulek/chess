set(LIBRARY_NAME
    chess
)

set(HEADERS_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}
)

set(SOURCES_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set(HEADERS
    ${HEADERS_DIR}/board/coordinates.h
    ${HEADERS_DIR}/board/board.h
    ${HEADERS_DIR}/pieces/piece.h
    ${HEADERS_DIR}/board/move.h
    ${HEADERS_DIR}/pieces/pawn.h
    ${HEADERS_DIR}/pieces/empty.h
    ${HEADERS_DIR}/pieces/rook.h
    ${HEADERS_DIR}/pieces/bishop.h
    ${HEADERS_DIR}/pieces/king.h
    ${HEADERS_DIR}/pieces/knight.h
    ${HEADERS_DIR}/pieces/queen.h
)

set(SOURCES
    ${SOURCES_DIR}/board/coordinates.cpp
    ${SOURCES_DIR}/board/board.cpp
    ${SOURCES_DIR}/pieces/pawn.cpp
    ${SOURCES_DIR}/pieces/empty.cpp
    ${SOURCES_DIR}/pieces/rook.cpp
    ${SOURCES_DIR}/pieces/bishop.cpp
    ${SOURCES_DIR}/pieces/king.cpp
    ${SOURCES_DIR}/pieces/knight.cpp
    ${SOURCES_DIR}/pieces/queen.cpp
)


set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

add_library(${LIBRARY_NAME} ${SOURCES} ${HEADERS})

add_library(Chess::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

target_include_directories(${LIBRARY_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
    $<INSTALL_INTERFACE:include/${LIBRARY_NAME}>
)

target_include_directories(${LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_subdirectory(tests)
