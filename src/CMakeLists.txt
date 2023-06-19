find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(lottie
    parser/check.h
    parser/check.cpp
)

target_link_libraries(lottie PRIVATE Qt6::Core)

target_include_directories(lottie PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
