#include "Neuron.hpp"
#include <cmath>


Neuron::Neuron(int previous_neurons_quantity, double *input_data)
{
	inputs_num = previous_neurons_quantity;
	weights = new double[previous_neurons_quantity];
	inputs = input_data;
}


Neuron::~Neuron()
{
	delete[] weights;
}


double Neuron::derivation()
{
	double result = 0;
	for (int i = 0; i < inputs_num; i++)
	{
		result += inputs[i] * weights[i];
	}
	return result;
}


double Neuron::sigm_conversion()
{
	return pow(1 + exp(-derivation()), -1);
}

double Neuron::weights_sum()
{
	double result = 0;

	for (int i = 0; i < inputs_num; i++)
		result += weights[i];

	return result;
}


void Neuron::set_weights(double* weights)
{
	for (int i = 0; i < inputs_num; i++)
		this->weights[i] = weights[i];
}


double* Neuron::get_weights()
{
	return weights;
}


void Neuron::set_inputs(double* inputs)
{
	this->inputs = inputs;
}

