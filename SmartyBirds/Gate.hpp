#pragma once
#include <SFML/Graphics.hpp>
#include <random>

class Gate
{
	sf::Image gate_img;
	sf::Texture gate_txt;

	sf::Vector2f default_position;
	sf::Vector2f position;

	float gates_height;
	const float upper_gate_height = 135;
	const float lower_gate_height = 121;
	const float gate_width = 26;
	const float clearance = 150;
	const float min_gates_height = 18;
	const float tip_width = 26;
	const float tip_height = 12;


	float get_next_gate_coords();

public:
	sf::Sprite gate_up;
	sf::Sprite gate_down;

	//sf::RectangleShape rect_upper_gate = sf::RectangleShape(sf::Vector2f(3 *(gate_width - 2), 3 * (upper_gate_height)));
	//sf::RectangleShape rect_upper_gate_tip = sf::RectangleShape(sf::Vector2f(3 * (tip_width), 3 * (tip_height)));
	//sf::RectangleShape rect_lower_gate = sf::RectangleShape(sf::Vector2f(3 * (gate_width - 2), 3 * (lower_gate_height)));
	//sf::RectangleShape rect_lower_gate_tip = sf::RectangleShape(sf::Vector2f(3 * (tip_width), 3 * (tip_height)));

	Gate(int x);
	~Gate(); 
	void update(float time);

	sf::Vector2f get_gate_coords();
};

