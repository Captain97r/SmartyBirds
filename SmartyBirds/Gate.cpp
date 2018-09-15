#include "Gate.hpp"


Gate::Gate(int x)
{
	default_position = sf::Vector2f(x, 0);
	gates_height = get_next_gate_coords();

	gate_img.loadFromFile("images/sprites.png");
	gate_txt.loadFromImage(gate_img);


	gate_up.setTexture(gate_txt);
	gate_up.setTextureRect(sf::IntRect(302, 0, gate_width, upper_gate_height));
	gate_up.setScale(sf::Vector2f(3, 3));

	position = sf::Vector2f(default_position.x, default_position.y - min_gates_height - gates_height);
	gate_up.setPosition(position);



	gate_down.setTexture(gate_txt);
	gate_down.setTextureRect(sf::IntRect(330, 0, gate_width, lower_gate_height));
	gate_down.setScale(sf::Vector2f(3, 3));

	position = sf::Vector2f(default_position.x, default_position.y + upper_gate_height * 3 + clearance - min_gates_height - gates_height);
	gate_down.setPosition(position);
/*
	rect_upper_gate.setPosition(default_position.x + 1 * 3, default_position.y - min_gates_height - gates_height);
	rect_lower_gate.setPosition(default_position.x + 1 * 3, default_position.y + upper_gate_height * 3 + clearance - min_gates_height - gates_height);
	rect_upper_gate_tip.setPosition(default_position.x, default_position.y - min_gates_height - gates_height + upper_gate_height * 3 - tip_height * 3);
	rect_lower_gate_tip.setPosition(default_position.x, default_position.y + upper_gate_height * 3 + clearance - min_gates_height - gates_height);

	rect_upper_gate.setFillColor(sf::Color::Red);
	rect_lower_gate.setFillColor(sf::Color::Red);
	rect_upper_gate_tip.setFillColor(sf::Color::Yellow);
	rect_lower_gate_tip.setFillColor(sf::Color::Yellow);*/
}


Gate::~Gate()
{
}


void Gate::update(float time)
{
	gate_up.move(-0.1 * time, 0);
	gate_down.move(-0.1 * time, 0);

	gates_height = get_next_gate_coords();

	if (gate_up.getPosition().x < -100)
	{
		position = sf::Vector2f(gate_up.getPosition().x + 1400, default_position.y - min_gates_height - gates_height);
		gate_up.setPosition(position);

		position = sf::Vector2f(gate_down.getPosition().x + 1400, default_position.y + upper_gate_height * 3 + clearance - min_gates_height - gates_height);
		gate_down.setPosition(position);

		//rect_upper_gate.setPosition(rect_upper_gate.getPosition().x + 1400, default_position.y - min_gates_height - gates_height);
		//rect_upper_gate_tip.setPosition(rect_upper_gate_tip.getPosition().x + 1400, default_position.y - min_gates_height - gates_height + upper_gate_height * 3 - tip_height * 3);
		//rect_lower_gate.setPosition(rect_lower_gate.getPosition().x + 1400, default_position.y + upper_gate_height * 3 + clearance - min_gates_height - gates_height);
		//rect_lower_gate_tip.setPosition(rect_lower_gate_tip.getPosition().x + 1400, default_position.y + upper_gate_height * 3 + clearance - min_gates_height - gates_height);
	}



	//rect_upper_gate.setPosition(rect_upper_gate.getPosition().x - 0.1 * time, rect_upper_gate.getPosition().y);
	//rect_lower_gate.setPosition(rect_lower_gate.getPosition().x - 0.1 * time, rect_lower_gate.getPosition().y);
	//rect_upper_gate_tip.setPosition(rect_upper_gate_tip.getPosition().x - 0.1 * time, rect_upper_gate_tip.getPosition().y);
	//rect_lower_gate_tip.setPosition(rect_lower_gate_tip.getPosition().x - 0.1 * time, rect_lower_gate_tip.getPosition().y);

}


float Gate::get_next_gate_coords()
{
	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_real_distribution<> distribution(0, 300);
	return (float)distribution(generator);
}


sf::Vector2f Gate::get_gate_coords()
{
	return sf::Vector2f(gate_up.getPosition().x + gate_width, gate_down.getPosition().y - (clearance / 2));
}