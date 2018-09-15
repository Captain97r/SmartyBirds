#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Game.hpp"
#include "NeuronWeb/Web.hpp"

int web_inputs_num = 2;
int web_hidden_layers_num = 1;
int web_neurons_in_hidden_layers[2] = { 6 };
int web_outputs_num = 1;

int main()
{
	for (int gen = 1;; gen++)
	{
		Game game;

		Web web1(web_inputs_num, web_hidden_layers_num, web_neurons_in_hidden_layers, web_outputs_num);
		Web web2(web_inputs_num, web_hidden_layers_num, web_neurons_in_hidden_layers, web_outputs_num);
		Web web3(web_inputs_num, web_hidden_layers_num, web_neurons_in_hidden_layers, web_outputs_num);
		Web web4(web_inputs_num, web_hidden_layers_num, web_neurons_in_hidden_layers, web_outputs_num);
		Web web5(web_inputs_num, web_hidden_layers_num, web_neurons_in_hidden_layers, web_outputs_num);

		game.go();
		//sf::Vector2f *distances = game.get_distances();

		while (game.window->isOpen())
		{
			web1.set_inputs(game.get_distances()[0]);
			web2.set_inputs(game.get_distances()[1]);
			web3.set_inputs(game.get_distances()[2]);
			web4.set_inputs(game.get_distances()[3]);
			web5.set_inputs(game.get_distances()[5]);

			if (web1.output_layer->get_outputs()[0] > 0.5) game.bird->jump();
			if (web2.output_layer->get_outputs()[0] > 0.5) game.bird2->jump();
			if (web3.output_layer->get_outputs()[0] > 0.5) game.bird3->jump();
			if (web4.output_layer->get_outputs()[0] > 0.5) game.bird4->jump();
			if (web5.output_layer->get_outputs()[0] > 0.5) game.bird5->jump();

			game.go();
			//distances = game.get_distances();

			//std::cout << distances[0].y << ", " << distances[1].y << ", " << distances[2].y << ", " << distances[3].y << ", " << distances[4].y << std::endl;

			std::cout << web1.output_layer->get_outputs()[0] << ", " << web2.output_layer->get_outputs()[0] << ", " << web3.output_layer->get_outputs()[0] << ", " << web4.output_layer->get_outputs()[0] << ", " << web5.output_layer->get_outputs()[0] << std::endl;

			if (game.is_all_birds_die()) break;
		}

		//game.~Game();
		web1.~Web();
		web2.~Web();
		web3.~Web();
		web4.~Web();
		web5.~Web();
		//delete distances;
	}

	return 0;
}