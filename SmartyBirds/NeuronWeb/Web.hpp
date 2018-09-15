#pragma once
#include <SFML/Graphics.hpp>
#include "InputLayer.hpp"
#include "HiddenLayer.hpp"

class Web
{
	InputLayer *input_layer;
	HiddenLayer **hidden_layers;

	int hidden_layers_num;
	int outputs_num;
	int* neurons_in_hidden_layers;
	int inputs_num;

public:
	HiddenLayer *output_layer;

	Web(int inputs_num, int hidden_layers_num, int* neurons_in_hidden_layers, int outputs_num);
	~Web();
	void back_propagation(double *targets);

	void set_inputs(double *inputs); 
	void set_inputs(sf::Vector2f inputs);
};

