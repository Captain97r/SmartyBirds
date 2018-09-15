#pragma once
#include <SFML/Graphics.hpp>

class Floor
{
	sf::Image floor_img;
	sf::Texture floor_txt;

public:
	sf::Sprite floor;

	Floor(int x);
	~Floor();
	void update(float time);
};

