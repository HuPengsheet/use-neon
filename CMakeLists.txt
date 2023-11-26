cmake_minimum_required(VERSION 3.10)
project(use-neon)
find_package(benchmark REQUIRED)
find_package(OpenMP REQUIRED)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)  
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv8-a -mcpu=cortex-a53+crc+fp+simd")

add_executable(test src/test.cpp)

add_executable(run src/add.cpp)
if(OpenMP_CXX_FOUND)
    target_compile_options(run PRIVATE ${OpenMP_CXX_FLAGS})
    target_link_libraries(run PRIVATE  OpenMP::OpenMP_CXX)
endif()
target_link_libraries(run PUBLIC benchmark::benchmark)