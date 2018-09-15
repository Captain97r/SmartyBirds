#pragma once
class InputLayer
{
public:
	double *outputs;

	InputLayer(int inputs_num);
	~InputLayer();
};

