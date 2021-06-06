set(LIBRARY_NAME
    communicator
)

set(HEADERS_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}
)

set(SOURCES_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set(HEADERS
    ${HEADERS_DIR}/communicator.h
    ${HEADERS_DIR}/command.h
)

set(SOURCES
    ${SOURCES_DIR}/communicator.cpp
    ${SOURCES_DIR}/command.cpp
)


set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

add_library(${LIBRARY_NAME} ${SOURCES} ${HEADERS})

add_library(Communicator::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

target_include_directories(${LIBRARY_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME}>
    $<INSTALL_INTERFACE:include/${LIBRARY_NAME}>
)

target_include_directories(${LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(
    ${LIBRARY_NAME}
   PUBLIC
    Logger::logger
)

add_subdirectory(tests)
