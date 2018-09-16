#include <random>
#include "GeneticAlghorithm.hpp"

GeneticAlghorithm::GeneticAlghorithm()
{
}


GeneticAlghorithm::~GeneticAlghorithm()
{
	result_web1 = nullptr;
	result_web2 = nullptr;
}



int GeneticAlghorithm::handle(Web* web1, Web* web2, Web* web3, Web* web4, Web* web5, float* fitnesses)
{
	float f[5];
	int result;
	int web_num;
	for (int i = 0; i < 5; i++)
		f[i] = fitnesses[i];
	
	quicksort(f, 0, 4);

	if (f[1] > 20) result = 2;
	else if (f[0] > 20) result = 1;
	else return 0;

	if (result >= 1)
	{
		web_num = search(fitnesses, f[0]);
		switch (web_num)
		{
		case 0:
			result_web1 = web1;
		case 1:
			result_web1 = web2;
		case 2:
			result_web1 = web3;
		case 3:
			result_web1 = web4;
		case 4:
			result_web1 = web5;
		}
	}

	if (result == 2)
	{
		web_num = search(fitnesses, f[1], web_num);
		switch (web_num)
		{
		case 0:
			result_web2 = web1;
		case 1:
			result_web2 = web2;
		case 2:
			result_web2 = web3;
		case 3:
			result_web2 = web4;
		case 4:
			result_web2 = web5;
		}
	}

	crossover();

	return result;
}


Web* GeneticAlghorithm::get_first_web()
{
	return result_web1;
}


Web* GeneticAlghorithm::get_second_web()
{
	return result_web2;
}


void GeneticAlghorithm::crossover()
{
	if (result_web2 == nullptr) return;

	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_real_distribution<> distribution1(1, 6);
	std::uniform_real_distribution<> distribution2(0, 1);

	int separator_pos = distribution1(generator);
	int first_parent = distribution2(generator);

	if (first_parent == 1)
	{
		Web *temp = result_web1;
		result_web1 = result_web2;
		result_web2 = temp;							//FIX
	}

	//int neurons_to_crossover = result_web1->get_hidden_neurons_quantity() + result_web1->get_output_neurons_quantity();

	//for (int i = 0; i < neurons_to_crossover; i++)
	//{
	//	if (i > separator_pos) // needs to think about 
	//}
}


int GeneticAlghorithm::search(float *f, float num, int except)
{
	for (int i = 0; i < 5; i++)
	{
		if (i == except) continue;
		if (f[i] == num) return i;
	}
	return 0;
}


int GeneticAlghorithm::partition(float *a, int p, int r)
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

void GeneticAlghorithm::quicksort(float *a, int p, int r)
{
	int q;
	if (p < r) {
		q = partition(a, p, r);
		quicksort(a, p, q - 1);
		quicksort(a, q + 1, r);
	}
}