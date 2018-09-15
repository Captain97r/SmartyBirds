#pragma once
class Neuron
{
	int inputs_num;
	double derivation();

public:
	double *weights;
	double *inputs;

	Neuron(int previous_neurons_quantity, double *input_data);
	~Neuron();
	double sigm_conversion();
	double weights_sum();
};

