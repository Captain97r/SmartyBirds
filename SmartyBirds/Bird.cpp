#include "Bird.hpp"
#include <iostream>


Bird::Bird()
{
	speed = sf::Vector2f(0, 0);
	position = sf::Vector2f(150, 350); 
	acceleration = sf::Vector2f(0, 500);

	bird_img.loadFromFile("images/sprites.png");

	bird_txt.loadFromImage(bird_img);

	bird.setTexture(bird_txt);
	bird.setTextureRect(sf::IntRect(264, 64, 17, 12));
	bird.setScale(sf::Vector2f(3, 3));
	bird.setPosition(position);
	circle.setPosition(position.x + 10, position.y + 1);
	//circle.setFillColor(sf::Color::Blue);
}


Bird::~Bird()
{
}


void Bird::update(float time)
{
	speed += acceleration * time * a;
	if (speed.y > 0.35) speed.y = 0.35;

	position += speed * time;

	bird.setPosition(position);
	circle.setPosition(position.x + 10, position.y + 1);
}


void Bird::jump()
{
	speed.y = -0.35;
}


sf::Vector2f Bird::get_coords()
{
	return sf::Vector2f(position.x + 24, position.y + 18);
}


sf::Vector2f Bird::get_distance_to_gate(Gate* gate)
{
	return gate->get_gate_coords() - get_coords();
}


void Bird::stop()
{
	speed = sf::Vector2f(0, 0);
	position = sf::Vector2f(-50, -50);
	acceleration = sf::Vector2f(0, 0);
}