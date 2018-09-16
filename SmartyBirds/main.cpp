#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Game.hpp"
#include "NeuronWeb/Web.hpp"
#include "GeneticAlghorithm.hpp"

int web_inputs_num = 2;
int web_hidden_layers_num = 1;
int web_neurons_in_hidden_layers[2] = { 6 };
int web_outputs_num = 1;
int web_nums = 100;

float max_fitness = 0;

int main()
{
	Web** web = new Web*[web_nums];
	bool first = true;
	bool create_new = true;

	for (int gen = 1;; gen++)
	{
		if (create_new)
		{
			for (int i = 0; i < web_nums; i++)
			{
				if (!first) delete web[i];
				web[i] = new Web(web_inputs_num, web_hidden_layers_num, web_neurons_in_hidden_layers, web_outputs_num);
			}
		}
		first = false;

		Game game(web_nums, gen);
		max_fitness = game.go(max_fitness);

		while (game.window->isOpen())
		{
			sf::Vector2f *dist = game.get_distances();
			double *outputs = new double[web_nums];

			for (int i = 0; i < web_nums; i++)
			{
				web[i]->set_inputs(dist[i]);

				outputs[i] = web[i]->get_outputs()[0];
				if (outputs[i] > 0.5) game.bird[i]->jump();
			}

			max_fitness = game.go(max_fitness);
			delete[] outputs;
			delete[] dist;

			if (game.is_all_birds_die()) break;
		}

		float *fitnesses = new float[web_nums];
		for (int i = 0; i < web_nums; i++)
			fitnesses[i] = game.bird[i]->get_fitness();

		create_new = web[0]->evolution(web, fitnesses, web_nums);

		delete[] fitnesses;

	}

	return 0;
}