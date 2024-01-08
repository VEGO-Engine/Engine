cmake_minimum_required(VERSION 3.10)

project(SDL_Minigame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/SDL)
add_subdirectory(lib/SDL_image)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
find_package(SDL_image REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(game ${SOURCES})

target_link_libraries(game PRIVATE SDL2::SDL2main)
target_link_libraries(game PRIVATE SDL2::SDL2 SDL2_image ${SDL2_LIBRARIES} ${SDL_IMAGE_LIBRARIES})