set(LIBRARY_NAME
    logger
)

set(HEADERS_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}
)

set(SOURCES_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set(HEADERS
    ${HEADERS_DIR}/logger.h
    ${HEADERS_DIR}/channels/i_logger_channel.h
    ${HEADERS_DIR}/channels/console_logger.h
    ${HEADERS_DIR}/channels/file_logger.h
)

set(SOURCES
    ${SOURCES_DIR}/logger.cpp
    ${SOURCES_DIR}/channels/console_logger.cpp
    ${SOURCES_DIR}/channels/file_logger.cpp
)

set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

add_library(${LIBRARY_NAME} ${SOURCES} ${HEADERS})

add_library(Logger::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

target_include_directories(${LIBRARY_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
    $<INSTALL_INTERFACE:include/${LIBRARY_NAME}>
)

target_include_directories(${LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_subdirectory(tests)
