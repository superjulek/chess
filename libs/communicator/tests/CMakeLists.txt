set(MODULE_NAME CommunicatorTests)

set(HEADERS
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_communicator.cpp
)

add_executable(${MODULE_NAME} ${SOURCES})


target_link_libraries(
    ${MODULE_NAME}
    PRIVATE
    gtest_main
    Communicator::communicator
)

include(GoogleTest)
gtest_discover_tests(${MODULE_NAME})
