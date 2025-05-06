cmake_minimum_required(VERSION 3.28)
project(turing)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB TEST_SRC test/*.cpp test/*.h)

set(MAIN_CPP main.cpp)

add_executable(turing
        ${MAIN_CPP}
        ${SOURCES}
)

add_executable(test_turing
        ${TEST_SRC}
        ${SOURCES}
)

# add_executable(test_turing ${TEST_SRC} ${SOURCES})

target_include_directories(turing PRIVATE
        src
        test
)

include_directories( ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(test_turing GTest::gtest GTest::gtest_main)
#gtest_discover_tests(test_turing)
