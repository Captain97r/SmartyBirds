#include "InputLayer.hpp"



InputLayer::InputLayer(int inputs_num)
{
	outputs = new double[inputs_num];

	for (int i = 0; i < inputs_num; i++)
		outputs[i] = 0;
}


InputLayer::~InputLayer()
{
	delete[] outputs;
}
