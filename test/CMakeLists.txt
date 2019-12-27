set(BINARY ${CMAKE_PROJECT_NAME}_test)

set(SOURCES ${TEST_SOURCES})

add_subdirectory(libs/googletest)

add_executable(${BINARY}
        Main.cpp
        MathHelperTests.cpp
        MathHelperTests.h)

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest_main)