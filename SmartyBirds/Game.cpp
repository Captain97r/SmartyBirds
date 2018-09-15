#include "Game.hpp"



Game::Game()
{
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

	bird = new Bird;
	bird2 = new Bird;
	bird3 = new Bird;
	bird4 = new Bird;
	bird5 = new Bird;


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

	//delete bird;

	delete event;
	delete window;
}


void Game::go()
{
	while (window->pollEvent(*event))
	{
		if (event->type == sf::Event::Closed)
			window->close();
	}
	time = clock.getElapsedTime().asMicroseconds();
	clock.restart();
	time = time / 700;

	collision_detector(bird);
	collision_detector(bird2);
	collision_detector(bird3);
	collision_detector(bird4);
	collision_detector(bird5);
	dispose_bird();

	update_objects();
	//key_listener();

	draw_objects();
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

	bird->update(time);
	bird2->update(time);
	bird3->update(time);
	bird4->update(time);
	bird5->update(time);
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

	window->draw(bird->bird);
	window->draw(bird2->bird);
	window->draw(bird3->bird);
	window->draw(bird4->bird);
	window->draw(bird5->bird);
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
	window->display();
}


void Game::key_listener()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !is_space_pressed)
	{
		is_space_pressed = true;
		bird->jump();
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

	if (gate1->get_gate_coords().x < min && gate1->get_gate_coords().x - bird->get_coords().x > 0) { nearest_gate = gate1; min = nearest_gate->get_gate_coords().x; }
	if (gate2->get_gate_coords().x < min && gate2->get_gate_coords().x - bird->get_coords().x > 0) { nearest_gate = gate2; min = nearest_gate->get_gate_coords().x; }
	if (gate3->get_gate_coords().x < min && gate3->get_gate_coords().x - bird->get_coords().x > 0) { nearest_gate = gate3; min = nearest_gate->get_gate_coords().x; }
	if (gate4->get_gate_coords().x < min && gate4->get_gate_coords().x - bird->get_coords().x > 0) { nearest_gate = gate4; min = nearest_gate->get_gate_coords().x; }

	sf::Vector2f distances[5] = {bird->get_distance_to_gate(nearest_gate), 
								 bird2->get_distance_to_gate(nearest_gate), 
								 bird3->get_distance_to_gate(nearest_gate),
								 bird4->get_distance_to_gate(nearest_gate), 
								 bird5->get_distance_to_gate(nearest_gate)};

	return distances;
}


void Game::dispose_bird()
{
	if (!bird->is_alive) bird->stop();
	if (!bird2->is_alive) bird2->stop();
	if (!bird3->is_alive) bird3->stop();
	if (!bird4->is_alive) bird4->stop();
	if (!bird5->is_alive) bird5->stop();
}


bool Game::is_all_birds_die()
{
	return !(bird->is_alive || bird2->is_alive || bird3->is_alive || bird4->is_alive || bird5->is_alive);
}