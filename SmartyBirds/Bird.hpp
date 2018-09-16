#pragma once
#include <SFML/Graphics.hpp>
#include "Gate.hpp"

class Bird
{
	sf::Image bird_img;
	sf::Texture bird_txt;

	float a = 0.0000013;

	sf::Vector2f speed;
	sf::Vector2f position;
	sf::Vector2f acceleration;

	float fitness;

public:
	sf::Sprite bird;
	sf::CircleShape circle = sf::CircleShape(17);
	bool is_alive = true;

	Bird();
	~Bird();
	void update(float time);
	void jump();

	sf::Vector2f get_coords();
	sf::Vector2f get_distance_to_gate(Gate *gate);
	void stop();
	float get_fitness();
};

