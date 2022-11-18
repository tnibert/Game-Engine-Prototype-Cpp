cmake_minimum_required(VERSION 3.0.0)
project(iron_lotus_engine VERSION 0.1.0)

add_executable(iron_lotus src/main.cpp)

target_link_libraries(iron_lotus SDL2main SDL2 SDL2_image)
