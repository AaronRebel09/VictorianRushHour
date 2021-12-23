#include "GameSprite.h"


GameSprite::GameSprite()
	:_vector(Vec2(0,0)),
_screenSize(Director::getInstance()->getWinSize())
{
}

GameSprite::~GameSprite()
{

}
