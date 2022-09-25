# find_package(doctest 2.3.3 REQUIRED)

#set(BINARY ${CMAKE_PROJECT_NAME}_tst)
#file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
#set(SOURCES ${TEST_SOURCES})
#add_executable(${BINARY} ${TEST_SOURCES})
#add_test(NAME ${BINARY} COMMAND ${BINARY})
## Свяжите библиотеку lib и библиотеку gtest, созданную src
#target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)

# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib/googletest-main/googletest-main)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Tests_run test_main.cpp test_classes.h)
include_directories(../src/BigInt)
target_link_libraries(Google_Tests_run big_int_lib gtest gtest_main)
