#include "Background.hpp"



Background::Background(int x)
{
	background_img.loadFromFile("images/sprites.png");

	background_txt.loadFromImage(background_img);

	background.setTexture(background_txt);
	background.setTextureRect(sf::IntRect(0, 0, 143, 255));
	background.setScale(sf::Vector2f(3, 3));
	background.setPosition(x, 0);
}


Background::~Background()
{
}


void Background::update(float time)
{
	background.move(-0.1 * time, 0);
	if (background.getPosition().x < -415) background.setPosition(1652 + background.getPosition().x, 0);
}