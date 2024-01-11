cmake_minimum_required(VERSION 3.10)

project(SDL_Minigame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(lib/SDL EXCLUDE_FROM_ALL)
add_subdirectory(lib/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(lib/libpng EXCLUDE_FROM_ALL)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${ZLIB_IMAGE_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2
    SDL2_image
    ${ZLIB_LIBRARY}
    ${PNG_LIBRARIES}
)

# Copy assets (if any) to build directory during build
file(COPY src/assets DESTINATION ${CMAKE_BINARY_DIR})