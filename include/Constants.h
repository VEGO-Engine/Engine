#pragma once

#include <cstddef>

using Group = std::size_t;
using Team = std::size_t;

constexpr int CHARACTER_COUNT = 4;

constexpr std::size_t MAX_COMPONENTS = 32;
constexpr std::size_t MAX_GROUPS = 32;
constexpr std::size_t MAX_STATS = 8;
constexpr std::size_t MAX_TEAMS = 8;

constexpr int SCREEN_SIZE_HEIGHT = 640;
constexpr int SCREEN_SIZE_WIDTH = 800;

constexpr int FPS = 60;

constexpr int TILE_SIZE = 32;

constexpr int MAP_SIZE_X = 25;
constexpr int MAP_SIZE_Y = 20;

constexpr int SPAWN_ATTEMPTS = 20;

constexpr int PLAY_LOOPED = -1;
constexpr int PLAY_ONCE = 0;

constexpr int MAX_VOLUME = 128;

