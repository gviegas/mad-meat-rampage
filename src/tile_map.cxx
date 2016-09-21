/*
* Created by Gustavo Viegas (2016/09)
*/

#include "tile_map.hxx"
#include "aux.hxx"
#include <fstream>
#include <sstream>
#include <iostream>

TileMap::TileMap(): m_tileSet({800, 600}) {
    loadConf("data/confs/map.conf");
    m_bg.scale(800.0 / 1920.0, 600.0 / 1080);
}

TileMap::~TileMap() {}

sf::FloatRect TileMap::getTileBB(const sf::Vector2u& pos) {}

sf::Vector2f TileMap::getPlayerStart() const { return m_playerStart; }
float TileMap::getGravity() const { return m_gravity; }

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
                m_tileSet.setTexture(aux::getBasePath() + texFile);
            } else if(attr == "START") {
                float x, y;
                sstream >> x >> y;
                m_playerStart = {x, y};
            } else if(attr == "GRAVITY") {
                float gravity;
                sstream >> gravity;
                m_gravity = gravity;
            } else if(attr == "TILE") {
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
void TileMap::loadMap(const std::string& fileName) {}

void TileMap::update(sf::RenderWindow* screen) {}
void TileMap::draw(sf::RenderWindow* screen) {
    screen->draw(m_bg);
}