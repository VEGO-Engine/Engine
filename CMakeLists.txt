cmake_minimum_required(VERSION 3.15)

project(SDL_Minigame)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_SHARED_LIBS FALSE)

add_subdirectory(extern/SDL EXCLUDE_FROM_ALL)
add_subdirectory(extern/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(extern/zlib EXCLUDE_FROM_ALL)
set(ZLIB_ROOT ${PROJECT_SOURCE_DIR}/extern/zlib)
set(ZLIB_LIBRARY zlib)
add_subdirectory(extern/libpng EXCLUDE_FROM_ALL)

include_directories(
    ${PROJECT_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES}
        include/ProjectileComponent.h
        include/AssetManager.h
        src/AssetManager.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2main
    SDL2::SDL2-static
    SDL2_image::SDL2_image-static
    ${ZLIB_LIBRARY}
    ${PNG_LIBRARIES}
)

file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${PROJECT_BINARY_DIR})