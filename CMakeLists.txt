cmake_minimum_required(VERSION 3.15)

project(SDL_Minigame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_SHARED_LIBS FALSE)

set(SDL2MIXER_VENDORED ON)
set(SDL2TTF_VENDORED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(extern/SDL EXCLUDE_FROM_ALL)
add_subdirectory(extern/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(extern/SDL_mixer EXCLUDE_FROM_ALL)
add_subdirectory(extern/SDL_ttf EXCLUDE_FROM_ALL)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2main
    SDL2::SDL2-static
    SDL2_image::SDL2_image-static
    SDL2_mixer::SDL2_mixer-static
    SDL2_ttf::SDL2_ttf-static
)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address -fno-omit-frame-pointer")
    target_link_libraries(${PROJECT_NAME} PRIVATE "-fsanitize=address")
endif()

file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${PROJECT_BINARY_DIR})


enable_testing()

add_executable(
  unittests
  unittests.cc
  ${SOURCES}
)

target_include_directories(unittests PRIVATE ${PROJECT_INCLUDE_DIR}
)

target_link_libraries(
  unittests
  GTest::gtest_main
  GTest::gmock_main
  SDL2::SDL2-static
  SDL2_image::SDL2_image-static
  SDL2_mixer::SDL2_mixer-static
  SDL2_ttf::SDL2_ttf-static
)

include(GoogleTest)
gtest_discover_tests(unittests)