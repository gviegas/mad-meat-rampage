/*
* Created by Gustavo Viegas (2016/09)
*/

#include "tile_map.hxx"
#include "aux.hxx"
#include "definitions.hxx"
#include <fstream>
#include <sstream>
#include <iostream>

TileMap::TileMap(): m_tileSet(
  {SCREEN_WIDTH / TILE_WIDTH, SCREEN_HEIGHT / TILE_HEIGHT},
  {TILE_WIDTH, TILE_HEIGHT})
{
    loadConf("data/confs/map.conf");
}

TileMap::~TileMap() {}

sf::FloatRect TileMap::getTileBBox(const sf::Vector2u& pos) { // TODO: return ref
    Tile* tile = m_tileSet.getTile(pos);
    if(!tile) { return {-1, -1, -1, -1}; } // TODO: get rid of this
    sf::FloatRect rect = tile->m_type->m_sprite.getLocalBounds();
    rect.left = tile->m_pos.x * getTileSize().x;
    rect.top = tile->m_pos.y * getTileSize().y;
    return rect;
}

float TileMap::getGravity() const { return m_gravity; }
const sf::Vector2u& TileMap::getTileSize() const { return m_tileSet.getTileSize(); }
const sf::Vector2u& TileMap::getGridSize() const { return m_tileSet.getGridSize(); }

bool TileMap::checkTile(const sf::Vector2u& gridPos) {
    return (m_tileSet.getTile(gridPos) == nullptr ? false : true);
}

void TileMap::clearTiles() { m_tileSet.clearTiles(); }

void TileMap::loadConf(const std::string& fileName) {
    std::ifstream file;
    file.open(aux::getBasePath() + fileName);
    if(!file.is_open()) {
        std::cerr << "ERROR: TileMap::loadConf - " << fileName << std::endl;
    } else {
        std::string line;
        while(std::getline(file, line)) {
            std::stringstream sstream(line);
            std::string attr;
            sstream >> attr;
            if(attr == "BACKGROUND") {
                std::string texFile;
                sstream >> texFile;
                m_texture.loadFromFile(aux::getBasePath() + texFile);
                m_bg.setTexture(m_texture);
            } else if(attr == "TILESET") {
                std::string texFile;
                sstream >> texFile;
                m_tileSet.setTexture(texFile);
            } else if(attr == "GRAVITY") {
                float gravity;
                sstream >> gravity;
                m_gravity = gravity;
            } else if(attr == "TILETYPE") {
                int id, top, left, width, height;
                sstream >> id >> top >> left >> width >> height;
                TileType* type = new TileType({top, left, width, height});
                if(!m_tileSet.addTileType(id, type)) {
                    delete type;
                    std::cerr << "ERROR: TileMap::loadConf - TILE " <<
                      id << std::endl;
                }
            }
        }
        file.close();
    }
}
void TileMap::loadMap(const std::string& fileName) {
    std::ifstream file;
    file.open(aux::getBasePath() + fileName);
    if(!file.is_open()) {
        std::cerr << "ERROR: TileMap::loadMap - " << fileName << std::endl;
    } else {
        std::string line;
        while(std::getline(file, line)) {
            std::stringstream sstream(line);
            std::string attr;
            sstream >> attr;
            if(attr == "TILE") {
                int id;
                unsigned int x, y;
                sstream >> id >> x >> y;
                if(!m_tileSet.addTile(id, {x, y})) {
                    std::cerr << "ERROR: TileMap::loadMap - TILE " <<
                      id << std::endl;
                }
            }
        }
        file.close();
    }

}

void TileMap::update(double updateInterval) {}

void TileMap::draw(sf::RenderWindow* screen) {
    screen->draw(m_bg);
    // TODO: culling (won't be needed if the map and the screen
    // have the same size...)
    for(unsigned int i = 0; i < m_tileSet.getGridSize().x; ++i) {
        for(unsigned int j = 0; j < m_tileSet.getGridSize().y; ++j) {
            Tile* tile;
            if(tile = m_tileSet.getTile({i, j})) {
                sf::Sprite& sprite = tile->m_type->m_sprite;
                sprite.setPosition(tile->m_pos.x * m_tileSet.getTileSize().x,
                  tile->m_pos.y * m_tileSet.getTileSize().y);
                screen->draw(sprite);
            }
        }

    }
}
