#pragma once#include <SFML/Graphics.hpp>
#include "Background.hpp"
#include "Floor.hpp"
#include "Gate.hpp"
#include "Bird.hpp"

class Game
{
	bool is_space_pressed;

	sf::Event *event;
	sf::Clock clock;
	float time;

	Background *background1;
	Background *background2;
	Background *background3;
	Background *background4;

	Floor *floor1;
	Floor *floor2;
	Floor *floor3;
	Floor *floor4;

	Gate *gate1;
	Gate *gate2;
	Gate *gate3;
	Gate *gate4;

	void update_objects();
	void draw_objects();
	void key_listener();
	void collision_detector(Bird *bird);
	void dispose_bird();

public:
	sf::RenderWindow *window;

	Bird *bird;
	Bird *bird2;
	Bird *bird3;
	Bird *bird4;
	Bird *bird5;

	Game();
	~Game();
	void go();

	sf::Vector2f* get_distances();
	bool is_all_birds_die();
};

