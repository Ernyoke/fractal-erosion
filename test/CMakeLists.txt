set(BINARY ${CMAKE_PROJECT_NAME}-test)

set(SOURCES ${TEST_SOURCES})

add_subdirectory(${CMAKE_SOURCE_DIR}/external/googletest build-googletest)

add_executable(${BINARY}
        Main.cpp
        MathHelperTests.cpp
        MathHelperTests.h)

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}-lib gtest_main)