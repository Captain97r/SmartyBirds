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