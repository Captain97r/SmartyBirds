#pragma once
#include <stdlib.h>
#include "NeuronWeb/Web.hpp"


class GeneticAlghorithm
{
	Web *result_web1;
	Web *result_web2;

	void crossover();

	int partition(float *a, int p, int r);
	void quicksort(float *a, int p, int r);
	int search(float *f, float num, int except = -1);

public:
	GeneticAlghorithm();
	~GeneticAlghorithm();

	int handle(Web* web1, Web* web2, Web* web3, Web* web4, Web* web5, float* fitnesses);
	Web* get_first_web();
	Web* get_second_web();
};

