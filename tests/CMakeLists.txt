find_package(Qt6 REQUIRED COMPONENTS Test)

add_executable(tests
    parser/test_check.cpp
)

target_link_libraries(tests PRIVATE Qt6::Test lottie)
