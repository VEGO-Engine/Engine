cmake_minimum_required(VERSION 3.15)

project(engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ENGINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ENGINE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(ENGINE_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_SHARED_LIBS FALSE)

set(SDL2MIXER_VENDORED ON)
set(SDL2TTF_VENDORED ON)

set(SDL2_SOURCE_DIR “${ENGINE_SOURCE_DIR}/extern/SDL”)

set(TMXLITE_STATIC_LIB TRUE)

add_subdirectory(extern/SDL EXCLUDE_FROM_ALL)
add_subdirectory(extern/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(extern/SDL_mixer EXCLUDE_FROM_ALL)
add_subdirectory(extern/SDL_ttf EXCLUDE_FROM_ALL)
add_subdirectory(extern/tmxlite/tmxlite EXCLUDE_FROM_ALL)

file(GLOB_RECURSE SOURCES ${ENGINE_SOURCE_DIR}/src/*.cpp)
add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${ENGINE_INCLUDE_DIR}
        ${ENGINE_SOURCE_DIR}/extern/json/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC # should be private when all SDL functionality has a wrapper
    SDL3::SDL3-static
    SDL3_image::SDL3_image-static
    SDL3_mixer::SDL3_mixer-static
    SDL3_ttf::SDL3_ttf-static
    tmxlite
)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") # -fsanitize=address -fno-omit-frame-pointer")
    #target_link_libraries(${PROJECT_NAME} PRIVATE "-fsanitize=address")
endif()

# link/copy compile commands to root dir
if(EXISTS ${PROJECT_BINARY_DIR}/compile_commands.json)
    file(CREATE_LINK
        ${PROJECT_BINARY_DIR}/compile_commands.json
        ${PROJECT_SOURCE_DIR}/compile_commands.json
        COPY_ON_ERROR SYMBOLIC
    )
endif()