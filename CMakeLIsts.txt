cmake_minimum_required(VERSION 3.22)

project(kremne)

find_package(verilator)

set(CMAKE_EXE_LINKER_FLAGS "-undefined dynamic_lookup")
add_executable(kremne src/main.cpp)
verilate(kremne SOURCES src/alu.v  VERILATOR_ARGS --trace)

#### GoogleTests ####
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(test)