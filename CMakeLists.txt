cmake_minimum_required(VERSION 3.0.0)
project(iron_lotus_engine VERSION 0.1.0)

add_definitions(-Wall -O2)
include_directories(/src)
add_executable(iron_lotus src/main.cpp src/sprite.cpp src/scene.cpp src/player.cpp src/gamestrategy.cpp src/town.cpp src/graphicscontext.cpp)

target_link_libraries(iron_lotus SDL2main SDL2 SDL2_image)
