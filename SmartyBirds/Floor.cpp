#include "Floor.hpp"



Floor::Floor(int x)
{
	floor_img.loadFromFile("images/sprites.png");

	floor_txt.loadFromImage(floor_img);

	floor.setTexture(floor_txt);
	floor.setTextureRect(sf::IntRect(146, 0, 154, 56));
	floor.setScale(sf::Vector2f(3, 3));
	floor.setPosition(x, 600);
}


Floor::~Floor()
{
}


void Floor::update(float time)
{
	floor.move(-0.1 * time, 0);
	if (floor.getPosition().x < -441) floor.setPosition(1746 + floor.getPosition().x, 600);
}