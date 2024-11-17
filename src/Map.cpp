#include "Map.h"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <optional>
#include <ranges>
#include <vector>

#include <SDL_error.h>
#include <SDL_render.h>

#include <tmxlite/Layer.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/Property.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Types.hpp>

#include "ColliderComponent.h"
#include "GameInternal.h"
#include "SpriteComponent.h"
#include "TextureManager.h"
#include "TileComponent.h"
#include "VEGO.h"

Map::Map(const char* path)
{
    if (!this->map.load(path)) {
        // TODO: log to console
        // TODO: error handling
    }

    std::vector<std::string> texturePaths = {};

    for (const auto& tileSet : map.getTilesets()) {
        texturePaths.emplace_back(tileSet.getImagePath());
    }

    this->mapData = {
        &map.getTilesets(),
        &map.getLayers(),
        &map.getTileCount(),
        &map.getTileSize(),
        &texturePaths
    };


    for (auto& layer : *this->mapData.mapLayers) {

        if (layer->getType() == tmx::Layer::Type::Tile) {
            loadTileLayer(layer->getLayerAs<tmx::TileLayer>());
            continue;
        }
        if (layer->getType() == tmx::Layer::Type::Object) {
            // spawn objects
            continue;
        }
    }
}

void Map::loadTileLayer(const tmx::TileLayer& layer)
{
    const std::vector<tmx::Property>& properties = layer.getProperties();
    int zIndex = getLayerProperty<int>(properties, "zIndex").value_or(0);
    bool collision = getLayerProperty<bool>(properties, "collision").value_or(false);

    const auto& tiles = layer.getTiles();

    // for each tile set
    auto tileConstructorRange = std::views::iota(0)
    | std::views::take(this->mapData.tileSets->size())
    // return the tile set metadata
    | std::views::transform([&](uint16_t i) {
        const char* texturePath = this->mapData.texturePaths->at(i).c_str();

        tmx::Vector2i textureSize;
        SDL_QueryTexture(
            VEGO_Game().textureManager->loadTexture(texturePath),
            nullptr,
            nullptr,
            &(textureSize.x),
            &(textureSize.y)
        );

        tmx::Vector2u tileCount2D = { textureSize.x / this->mapData.mapTileSize->x, textureSize.y / this->mapData.mapTileSize->y };

        uint32_t tileCount = this->mapData.tileSets->at(i).getTileCount();
        uint32_t firstGID = this->mapData.tileSets->at(i).getFirstGID();

        return TileSetData { texturePath, textureSize, tileCount, tileCount2D, firstGID };
    })
    | std::views::transform([=, this](const TileSetData& data) {
        // for each tile on the tile set
        return std::views::iota(0)
        | std::views::take(this->mapData.mapSize->x * this->mapData.mapSize->y)
        // only take tiles that are on the ID range of the tile set
        | std::views::filter([=](uint16_t idx) {
            return
                idx < tiles.size()
                && tiles[idx].ID >= data.firstGID
                && tiles[idx].ID < (data.firstGID + data.tileCount);
        })
        // extract tile data
        | std::views::transform([=, this](uint16_t idx) {
            const auto x = idx % this->mapData.mapSize->x;
            const auto y = idx / this->mapData.mapSize->x;

            const auto idIndex = (tiles[idx].ID - data.firstGID);

            uint32_t u = idIndex % data.tileCount2D.x;
            uint32_t v = idIndex / data.tileCount2D.y;
            u *= this->mapData.mapTileSize->x; // TODO: we should be using the tile set size, as this may be different from the map's grid size
            v *= this->mapData.mapTileSize->y;

            // normalise the UV
            u /= data.textureSize.x;
            v /= data.textureSize.y;

            // vert pos
            const float tilePosX = static_cast<float>(x) * this->mapData.mapTileSize->x;
            const float tilePosY = (static_cast<float>(y) * this->mapData.mapTileSize->y);

            // return tile data as a function to spawn said tile
            return std::function<void()>(
                [tilePosX, tilePosY, capture0 = *this->mapData.mapTileSize, u, v, zIndex, capture1 = data.texturePath, collision] {
                    Map::addTile(tilePosX, tilePosY, capture0, u, v, zIndex, capture1, collision);
                }
            );
        });
    })
    // 2D view to 1D vector; might be better keep as view with scene management
    | std::views::join
    | std::ranges::to<std::vector>();

    this->tileConstructors.insert(this->tileConstructors.end(), tileConstructorRange.begin(), tileConstructorRange.end());
}

void Map::addTile(float x, float y, const tmx::Vector2u& mapTileSize, int u, int v, int zIndex, const char* texturePath, bool hasCollision)
{
    auto& tile(VEGO_Game().manager.addEntity());

    tile.addComponent<TransformComponent>(x, y, mapTileSize.x, mapTileSize.y, 1);
    tile.addComponent<SpriteComponent>("assets/grassy-river-tiles.png" /*texturePath*/, v, u, zIndex); // why does uv need to be reversed?

    if (hasCollision) {
        // tag currently does not have a clear purposes, TODO: figure out appropriate tag name
        tile.addComponent<ColliderComponent>("hello I am a collider of a tile!");
        tile.addGroup((size_t)Entity::GroupLabel::MAPTILES);
    }
}

void Map::generateTiles() 
{
    std::ranges::for_each(this->tileConstructors, [](auto& function) {
        function();
    });
}