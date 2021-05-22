set(LIBRARY_NAME
    view
)

set(HEADERS_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}
)

set(SOURCES_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set(HEADERS
    ${HEADERS_DIR}/i_view.h
    ${HEADERS_DIR}/viewers/console_viewer.h
)

set(SOURCES
    ${SOURCES_DIR}/viewers/console_viewer.cpp
)

set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

add_library(${LIBRARY_NAME} ${SOURCES} ${HEADERS})

add_library(View::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

target_include_directories(${LIBRARY_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
    $<INSTALL_INTERFACE:include/${LIBRARY_NAME}>
)

target_include_directories(${LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_subdirectory(tests)

target_link_libraries(
    ${LIBRARY_NAME}
    PRIVATE
    Chess::chess
)
