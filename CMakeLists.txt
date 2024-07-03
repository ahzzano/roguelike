cmake_minimum_required(VERSION "3.19.2")

project(roguelike-main)
set(CMAKE_CXX_STANDARD 20)

add_executable(rougelike-main "src/main.cpp")

target_include_directories(rougelike-main "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_link_libraries(roguelike-main PRIVATE libSDL2)
