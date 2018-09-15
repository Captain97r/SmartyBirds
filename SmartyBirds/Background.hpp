#pragma once
#include <SFML/Graphics.hpp>

class Background
{
	sf::Image background_img;
	sf::Texture background_txt;

public:
	sf::Sprite background;

	Background(int x);
	~Background();
	void update(float time);
};

