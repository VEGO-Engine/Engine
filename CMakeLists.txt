cmake_minimum_required(VERSION 3.10)

project(SDL_Minigame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# libpng stuff
set(PNG_SHARED ON CACHE BOOL "" FORCE)
set(PNG_STATIC OFF CACHE BOOL "" FORCE)
set(PNG_EXECUTABLES OFF CACHE BOOL "" FORCE) # we only want lib
set(PNG_TESTS OFF CACHE BOOL "" FORCE) # we only want lib
set(SKIP_INSTALL_ALL OFF CACHE BOOL "" FORCE) # we only want lib

include_directories(libpng)

add_subdirectory(lib/SDL)
add_subdirectory(lib/SDL_image)
add_subdirectory(lib/libpng)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
find_package(SDL_image REQUIRED)

find_package(ZLIB REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/libpng)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(game ${SOURCES})

target_link_libraries(game PRIVATE SDL2::SDL2main)
target_link_libraries(game PRIVATE SDL2::SDL2 SDL2_image ${SDL2_LIBRARIES} ${SDL_IMAGE_LIBRARIES})
target_link_libraries(game PRIVATE ZLIB::ZLIB)
target_link_libraries(game PRIVATE png)