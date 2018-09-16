#include <random>
#include <iostream>
#include "Web.hpp"


Web::Web(int inputs_num, int hidden_layers_num, int* neurons_in_hidden_layers, int outputs_num)
{
	this->hidden_layers_num = hidden_layers_num;
	this->outputs_num = outputs_num;
	this->neurons_in_hidden_layers = neurons_in_hidden_layers;
	this->inputs_num = inputs_num;

	int prev_inputs_num;
	double *prev_inputs;

	input_layer = new InputLayer(inputs_num);
	prev_inputs_num = inputs_num;
	prev_inputs = input_layer->outputs;

	hidden_layers = new HiddenLayer*[hidden_layers_num];
	for (int i = 0; i < hidden_layers_num; i++)
	{
		hidden_layers[i] = new HiddenLayer(prev_inputs_num, neurons_in_hidden_layers[i], prev_inputs);
		prev_inputs_num = neurons_in_hidden_layers[i];
		prev_inputs = hidden_layers[i]->get_outputs();
	}

	output_layer = new HiddenLayer(prev_inputs_num, outputs_num, prev_inputs);

	delete[] prev_inputs;
}


Web::~Web()
{
	/*delete[] input_layer;
	delete[] output_layer;

	for (int i = 0; i < hidden_layers_num; i++)
		delete[] hidden_layers[i];

	delete[] hidden_layers;
	delete[] neurons_in_hidden_layers;*/
}


void Web::back_propagation(double *targets)
{
	targets = output_layer->back_propagation(targets, outputs_num);

	for (int i = hidden_layers_num - 1; i >= 0; i--)
		targets = hidden_layers[i]->back_propagation(targets, neurons_in_hidden_layers[i]);
}


void Web::set_inputs(double *inputs)
{
	for (int i = 0; i < inputs_num; i++)
		input_layer->outputs[i] = inputs[i];

	for (int i = 1; i < hidden_layers_num; i++)
		for (int j = 0; j < neurons_in_hidden_layers[i]; j++)
			hidden_layers[i]->neurons[j]->inputs = hidden_layers[i - 1]->get_outputs();

	for (int i = 0; i < outputs_num; i++)
		output_layer->neurons[i]->inputs = hidden_layers[hidden_layers_num - 1]->get_outputs();
}


void Web::set_inputs(sf::Vector2f inputs)
{
		input_layer->outputs[0] = inputs.x / 500;
		input_layer->outputs[1] = inputs.y / 100;

	for (int i = 1; i < hidden_layers_num; i++)
		for (int j = 0; j < neurons_in_hidden_layers[i]; j++)
			hidden_layers[i]->neurons[j]->inputs = hidden_layers[i - 1]->get_outputs();

	for (int i = 0; i < outputs_num; i++)
		output_layer->neurons[i]->inputs = hidden_layers[hidden_layers_num - 1]->get_outputs();
}


double* Web::get_outputs()
{
	return output_layer->get_outputs();
}


bool Web::evolution(Web** webs, float* fitnesses, int num)
{
	Web** best_webs = new Web*[num];
	
	int worth_webs_nums = selection(best_webs, webs, fitnesses, num);
	if (worth_webs_nums > 0)
		crossover(webs, best_webs, num, worth_webs_nums);

	for (int i = 0; i < worth_webs_nums; i++)
		delete best_webs[i];
	delete[] best_webs;

	mutation(webs, num);

	return worth_webs_nums < 2;
}

int Web::selection(Web** best_webs, Web** webs, float* fitnesses, int num)
{
	float *f = new float[num];
	int result = 0;
	int web_num;
	for (int i = 0; i < num; i++)
		f[i] = fitnesses[i];

	quicksort(f, 0, num - 1);

	for (int i = 0; i < num; i++)
	{
		if (f[i] > 100) result++;
	}

	int except = -1;
	for (int i = 0; i < result; i++)
	{
		web_num = search(fitnesses, f[i], num, except);
		best_webs[i] = new Web(*webs[web_num]);
		except = web_num;
	}

	std::cout << result << std::endl;
	delete[] f;

	return result;
}


void Web::crossover(Web** webs, Web** best_webs, int num, int best_num)
{
	// num гарантированно четное!
	//Web** result_webs = new Web*[num];
	//for (int i = 0; i < num; i++)
	//	result_webs[i] = new Web(this->inputs_num, this->hidden_layers_num, this->neurons_in_hidden_layers, this->outputs_num);

	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_real_distribution<> separator_pos_distribution(1, 6);
	std::uniform_real_distribution<> parent_distribution(0, best_num);

	int neurons_to_crossover = 0;
	for (int i = 0; i < hidden_layers_num; i++)
		neurons_to_crossover += neurons_in_hidden_layers[i];

	for (int i = 0; i < num; i++)
	{
		int separator_pos = separator_pos_distribution(generator);
		int first_parent = parent_distribution(generator);
		int second_parent = parent_distribution(generator);
		if(best_num != 1)
			while (second_parent == first_parent)
				second_parent = parent_distribution(generator);

		for (int j = 0; j < neurons_to_crossover; j ++)
		{
			if (j > separator_pos) webs[i]->hidden_layers[0]->neurons[j]->set_weights(best_webs[second_parent]->hidden_layers[0]->neurons[j]->get_weights());
			else webs[i]->hidden_layers[0]->neurons[j]->set_weights(best_webs[first_parent]->hidden_layers[0]->neurons[j]->get_weights());
		}
		webs[i]->output_layer->neurons[0]->set_weights(best_webs[first_parent]->output_layer->neurons[0]->get_weights());

	}
}


void Web::mutation(Web** webs, int num)
{
	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_real_distribution<> mutate_distribution(0, 1000);
	std::uniform_real_distribution<> mutation_chance_distribution(0, 100);

	double *weights = nullptr;

	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < this->neurons_in_hidden_layers[0]; j++)
		{
			weights = webs[i]->hidden_layers[0]->neurons[j]->get_weights();
			for (int k = 0; k < inputs_num; k++)
			{
				if (mutation_chance_distribution(generator) < 20)
				{
					float mutation_factor = 1 + ((((float)(mutate_distribution(generator)) / 1000) - 0.5) * 3 + (((float)(mutate_distribution(generator)) / 1000) - 0.5));
					weights[k] *= mutation_factor;
				}
			}
			webs[i]->hidden_layers[0]->neurons[j]->set_weights(weights);
		}
	}
	//delete[] weights;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int Web::search(float *f, float num, int n, int except)
{
	for (int i = 0; i < n; i++)
	{
		if (i == except) continue;
		if (f[i] == num) return i;
	}
	return 0;
}


int Web::partition(float *a, int p, int r)
{
	float x = *(a + r);
	int i = p - 1;
	int j;
	float tmp;
	for (j = p; j < r; j++)
	{
		if (*(a + j) >= x)
		{
			i++;
			tmp = *(a + i);
			*(a + i) = *(a + j);
			*(a + j) = tmp;
		}
	}
	tmp = *(a + r);
	*(a + r) = *(a + i + 1);
	*(a + i + 1) = tmp;
	return i + 1;
}

void Web::quicksort(float *a, int p, int r)
{
	int q;
	if (p < r) {
		q = partition(a, p, r);
		quicksort(a, p, q - 1);
		quicksort(a, q + 1, r);
	}
}