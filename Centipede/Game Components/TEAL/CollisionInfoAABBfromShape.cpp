// CollisionInfoAABBfromShape.h
// Andre Berthiaume, July 2012
// July 2019: memory clean up

#include "CollisionInfoAABBfromShape.h"
#include "WindowManager.h"

sf::FloatRect CollisionInfoAABBfromShape::getAABB(){ return shape->getGlobalBounds(); }
sf::Vector2f CollisionInfoAABBfromShape::getPosition(){ return shape->getPosition(); }
float CollisionInfoAABBfromShape::getRotation(){ return shape->getRotation();}
sf::Transform CollisionInfoAABBfromShape::getTransform(){ return shape->getTransform(); }

void CollisionInfoAABBfromShape::Draw(){ WindowManager::Window().draw( *shape ); }