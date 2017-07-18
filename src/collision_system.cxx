/*
* Created by Gustavo Viegas (2016/09)
*/

#include "collision_system.hxx"

CollisionSystem::CollisionSystem() {}
CollisionSystem::~CollisionSystem() {}

bool CollisionSystem::isColliding(Collidable* collidable,
  sf::FloatRect tileRect, sf::FloatRect& intersection)
{
    return (collidable->getBBox().intersects(
      tileRect, intersection));
}

bool CollisionSystem::isColliding(Collidable* collidA,
  Collidable* collidB, sf::FloatRect& intersection)
{
    return (collidA->getBBox().intersects(
      collidB->getBBox(), intersection));
}

// TODO: a better algorithm to choose the right collision axis
Axis CollisionSystem::getCollisionAxis(sf::FloatRect& intersection) {
    return (intersection.width < intersection.height ?
      Axis::X : Axis::Y);
}

void CollisionSystem::checkTileCollisions(Collidable* collidable,
  TileMap* map)
{
    sf::FloatRect rect = collidable->getBBox();
    int rx = map->getTileSize().x;
    int ry = map->getTileSize().y;
    for(int x = rect.left / rx; x <= (rect.left + rect.width) / rx; ++x) {
        for(int y = rect.top / ry; y <= (rect.top + rect.height) / ry; ++y) {
            sf::FloatRect tileRect = map->getTileBBox(
              {static_cast<unsigned int>(x), static_cast<unsigned int>(y)});
            sf::FloatRect intersection;
            if(isColliding(collidable, tileRect, intersection)) {
                CollisionData data {collidable, tileRect,
                  getCollisionAxis(intersection)};
                m_collisions.emplace_back(std::make_pair(
                  CollisionTarget::Tile, data));
            }
        }
    }
}

void CollisionSystem::checkCollidableCollisions(Collidable* collidable,
  Collidables& collidables)
{
    for(auto& iter : collidables) {
        sf::FloatRect intersection;
        if(isColliding(collidable, iter, intersection)) {
            CollisionData data {collidable, iter,
              getCollisionAxis(intersection)};
            m_collisions.emplace_back(std::make_pair(
              CollisionTarget::Collidable, data));
        }
    }
}

void CollisionSystem::checkCollisions(Collidable* collidable,
  Collidables& collidables, TileMap* map)
{
    checkTileCollisions(collidable, map);
    checkCollidableCollisions(collidable, collidables);
}

void CollisionSystem::resolveCollisions() {
    for(auto& iter : m_collisions) {
        if(iter.first == CollisionTarget::Tile) {
            iter.second.m_collidable->onTileCollision(
              iter.second.m_tileRect, iter.second.m_axis);
        } else if(iter.first == CollisionTarget::Collidable) {
            iter.second.m_collidable->onCollision(
              iter.second.m_other, iter.second.m_axis);
        }
    }
    m_collisions.clear();
}
