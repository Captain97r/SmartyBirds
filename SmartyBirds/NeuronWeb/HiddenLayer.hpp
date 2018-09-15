#pragma once
#include "Neuron.hpp"

class HiddenLayer
{
	int inputs_quantity;
	int neurons_quantity;

	void set_weights();

public:
	Neuron **neurons;

	HiddenLayer(int inputs_quantity, int neurons_quantity, double *inputs);
	~HiddenLayer();
	double* back_propagation(double *targets, int targets_length);
	double* get_outputs();
};

