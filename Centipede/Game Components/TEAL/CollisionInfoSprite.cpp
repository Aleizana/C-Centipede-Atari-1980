// CollisionInfoSprite.cpp
// Andre Berthiaume, July 2012
// July 2019: memory clean up

#include "CollisionInfoSprite.h"
#include "WindowManager.h"

sf::Vector2f CollisionInfoSprite::getPosition(){ return sprite->getPosition(); }
float CollisionInfoSprite::getRotation(){ return sprite->getRotation();}
sf::Transform CollisionInfoSprite::getTransform(){ return sprite->getTransform(); }

void CollisionInfoSprite::Draw(){ WindowManager::Window().draw( *sprite ); }

sf::FloatRect CollisionInfoSprite::getAABB()
{
	return sprite->getGlobalBounds();
}

bool CollisionInfoSprite::PairwiseCollisionTest( CollisionInfo *other )
{
	return other->CollisionTest( sprite, bitmap);
}

bool CollisionInfoSprite::CollisionTest( sf::FloatRect *r )
{
	return CollisionTools::RectangleSpriteIntersection( *r, *sprite, *bitmap);
}

bool CollisionInfoSprite::CollisionTest( sf::Shape *s)
{
	return CollisionTools::ShapeSpriteIntersection(*s, *sprite, *bitmap);
}

bool CollisionInfoSprite::CollisionTest( sf::Sprite *s, CollisionTools::TextureBitmap *b )
{
	return CollisionTools::SpriteSpriteIntersection(*sprite, *bitmap, *s, *b);
}