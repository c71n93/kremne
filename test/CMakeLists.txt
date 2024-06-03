add_executable(alu-test
    alu-test.cpp
)
verilate(alu-test SOURCES ${CMAKE_SOURCE_DIR}/src/alu.v  VERILATOR_ARGS --trace)
target_link_libraries(alu-test PUBLIC
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(alu-test)
