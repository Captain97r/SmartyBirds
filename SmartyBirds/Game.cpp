#include <sstream>
#include "Game.hpp"



Game::Game(int num, int generation)
{
	this->generation = generation;
	this->num = num;
	is_space_pressed = false;

	window = new sf::RenderWindow(sf::VideoMode(1000, 765), "Smarty Birds");
	event = new sf::Event();

	background1 = new Background(0);
	background2 = new Background(413);
	background3 = new Background(826);
	background4 = new Background(1239);

	floor1 = new Floor(0);
	floor2 = new Floor(441);
	floor3 = new Floor(882);
	floor4 = new Floor(1323);

	gate1 = new Gate(1050);
	gate2 = new Gate(1400);
	gate3 = new Gate(1750);
	gate4 = new Gate(2100);

	bird = new Bird*[num];
	for (int i = 0; i < num; i++)
	{
		bird[i] = new Bird;
	}


	do
	{
		time = clock.getElapsedTime().asSeconds();
	} while (time < 1);
	clock.restart();
}


Game::~Game()
{
	delete background1;
	delete background2;
	delete background3;
	delete background4;

	delete floor1;
	delete floor2;
	delete floor3;
	delete floor4;

	delete gate1;
	delete gate2;
	delete gate3;
	delete gate4;

	for (int i = 0; i < num; i++)
		delete bird[i];
	delete[] bird;

	delete event;
	delete window;
}


float Game::go(float f)
{
	max_fitness = f;
	while (window->pollEvent(*event))
	{
		if (event->type == sf::Event::Closed)
			window->close();
	}
	time = clock.getElapsedTime().asMicroseconds();
	clock.restart();
	time = time / 300;

	for (int i = 0; i < num; i++)
		collision_detector(bird[i]);
	dispose_bird();

	update_objects();
	//key_listener();

	draw_objects();


	for (int i = 0; i < num; i++)
		if (bird[i]->is_alive)
		{
			sc = bird[i]->get_fitness();
			if (sc > max_fitness) max_fitness = sc;
		}

	return max_fitness;
}


void Game::update_objects()
{
	background1->update(time);
	background2->update(time);
	background3->update(time);
	background4->update(time);

	floor1->update(time);
	floor2->update(time);
	floor3->update(time);
	floor4->update(time);

	gate1->update(time);
	gate2->update(time);
	gate3->update(time);
	gate4->update(time);

	for (int i = 0; i < num; i++)
		bird[i]->update(time);
}


void Game::draw_objects()
{
	window->clear();
	window->draw(background1->background);
	window->draw(background2->background);
	window->draw(background3->background);
	window->draw(background4->background);

	window->draw(gate1->gate_up);
	window->draw(gate1->gate_down);
	window->draw(gate2->gate_up);
	window->draw(gate2->gate_down);
	window->draw(gate3->gate_up);
	window->draw(gate3->gate_down);
	window->draw(gate4->gate_up);
	window->draw(gate4->gate_down);

	window->draw(floor1->floor);
	window->draw(floor2->floor);
	window->draw(floor3->floor);
	window->draw(floor4->floor);

	for (int i = 0; i < num; i++)
		window->draw(bird[i]->bird);
	//window->draw(bird->circle);
	//window.draw(gate1.rect_lower_gate);
	//window.draw(gate1.rect_upper_gate);
	//window.draw(gate1.rect_lower_gate_tip);
	//window.draw(gate1.rect_upper_gate_tip);
	//window.draw(gate2.rect_lower_gate);
	//window.draw(gate2.rect_upper_gate);
	//window.draw(gate2.rect_lower_gate_tip);
	//window.draw(gate2.rect_upper_gate_tip);
	//window.draw(gate3.rect_lower_gate);
	//window.draw(gate3.rect_upper_gate);
	//window.draw(gate3.rect_lower_gate_tip);
	//window.draw(gate3.rect_upper_gate_tip);
	//window.draw(gate4.rect_lower_gate);
	//window.draw(gate4.rect_upper_gate);
	//window.draw(gate4.rect_lower_gate_tip);
	//window.draw(gate4.rect_upper_gate_tip);


	draw_text();

	window->display();
}


void Game::draw_text()
{
	sf::Font font;
	font.loadFromFile("times.ttf");
	sf::Text text_alive("", font, 20);
	text_alive.setFillColor(sf::Color::Black);
	text_alive.setStyle(sf::Text::Regular);

	sf::Text text_fitness("", font, 20);
	text_fitness.setFillColor(sf::Color::Black);
	text_fitness.setStyle(sf::Text::Regular);

	sf::Text text_max_fitness("", font, 20);
	text_max_fitness.setFillColor(sf::Color::Black);
	text_max_fitness.setStyle(sf::Text::Regular);

	sf::Text text_generation("", font, 20);
	text_generation.setFillColor(sf::Color::Black);
	text_generation.setStyle(sf::Text::Regular);


	int n = 0;
	for (int i = 0; i < num; i++)
		if (bird[i]->is_alive)
			n++;


	std::ostringstream gen;
	gen << generation;
	text_generation.setString("Generation: " + gen.str());
	text_generation.setPosition(10, 630);

	std::ostringstream score;
	score << sc;
	text_fitness.setString("Fitness: " + score.str());
	text_fitness.setPosition(10, 660);

	std::ostringstream max_f;
	max_f << max_fitness;
	text_max_fitness.setString("Max fitness: " + max_f.str());
	text_max_fitness.setPosition(10, 690);

	std::ostringstream num_of_alive;
	num_of_alive << n;
	text_alive.setString("Birds alive: " + num_of_alive.str());
	text_alive.setPosition(10, 720);


	window->draw(text_generation);
	window->draw(text_alive);
	window->draw(text_fitness);
	window->draw(text_max_fitness);
}


void Game::key_listener()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !is_space_pressed)
	{
		is_space_pressed = true;
		//bird->jump();
	}
	else if (event->type == sf::Event::KeyReleased)
		is_space_pressed = false;
}


void Game::collision_detector(Bird *bird)
{
	if (gate1->gate_up.getGlobalBounds().intersects(bird->circle.getGlobalBounds()) ||
		gate1->gate_down.getGlobalBounds().intersects(bird->circle.getGlobalBounds()) ||
		gate2->gate_up.getGlobalBounds().intersects(bird->circle.getGlobalBounds()) ||
		gate2->gate_down.getGlobalBounds().intersects(bird->circle.getGlobalBounds()) ||
		gate3->gate_up.getGlobalBounds().intersects(bird->circle.getGlobalBounds()) ||
		gate3->gate_down.getGlobalBounds().intersects(bird->circle.getGlobalBounds()) ||
		gate4->gate_up.getGlobalBounds().intersects(bird->circle.getGlobalBounds()) ||
		gate4->gate_down.getGlobalBounds().intersects(bird->circle.getGlobalBounds()) ||
		bird->bird.getPosition().y > 565 || bird->bird.getPosition().y < -100)
		bird->is_alive = false;
}


sf::Vector2f* Game::get_distances()
{
	int min = 10000;
	Gate *nearest_gate = gate1;
	Bird *alive = nullptr;

	for (int i = 0; i < num; i++)
	{
		if (bird[i]->is_alive) alive = bird[i];
	}

	if (gate1->get_gate_coords().x < min && gate1->get_gate_coords().x - alive->get_coords().x > 0) { nearest_gate = gate1; min = nearest_gate->get_gate_coords().x; }
	if (gate2->get_gate_coords().x < min && gate2->get_gate_coords().x - alive->get_coords().x > 0) { nearest_gate = gate2; min = nearest_gate->get_gate_coords().x; }
	if (gate3->get_gate_coords().x < min && gate3->get_gate_coords().x - alive->get_coords().x > 0) { nearest_gate = gate3; min = nearest_gate->get_gate_coords().x; }
	if (gate4->get_gate_coords().x < min && gate4->get_gate_coords().x - alive->get_coords().x > 0) { nearest_gate = gate4; min = nearest_gate->get_gate_coords().x; }

	sf::Vector2f *distances = new sf::Vector2f[num];

	for (int i = 0; i < num; i++)
		distances[i] = bird[i]->get_distance_to_gate(nearest_gate);

	return distances;
}


void Game::dispose_bird()
{
	for (int i = 0; i < num; i++)
		if (!bird[i]->is_alive) bird[i]->stop();
}


bool Game::is_all_birds_die()
{
	bool result = false;

	for (int i = 0; i < num; i++)
		result = result || bird[i]->is_alive;
	return !result;
}