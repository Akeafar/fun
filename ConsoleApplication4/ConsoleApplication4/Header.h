#include <iostream>
#include <time.h>


#define population_size 5

using namespace std;

class Gene{
public:
	float alleles[4];
	float fitness;
	float total_fitness;
	float chance_for_conceiving;

};



class Population{
public:
	
	float ax, bx, cx, dx; //koeficienti
	float result; //resultat urovneni9 (to k 4emu doljno stremit's9)

	Gene population[population_size];
	
	Gene GetGene(int i)
	{
		return population[i];
	}

	Population(float a, float b, float c, float d, float res)
	{
		ax = a;
		bx = b;
		cx = c;
		dx = d;
		result = res;
	}



	void Create_first_generation()
	{
		for (int i = 0; i < population_size; i++)
		{
			for (int j = 0; j < 4; j++) //randomim zna4eni9 genov
			{
				population[i].alleles[j] = rand() % 30+1;
			}
		}

	}

	void Calculate_fiteness_for_population()
	{
		for (int i = 0; i < population_size; i++)
		{
			population[i].total_fitness= ax*population[i].alleles[0] + bx*population[i].alleles[1] + cx*population[i].alleles[2] + dx*population[i].alleles[3];
			population[i].fitness = 1/abs(population[i].total_fitness-result);
		}
	}

	void Calculate_fiteness_for_unite(Gene &new_gene)
	{
		new_gene.total_fitness = ax*new_gene.alleles[0] + bx*new_gene.alleles[1] + cx*new_gene.alleles[2] + dx*new_gene.alleles[3];
		new_gene.fitness = 1 / abs(new_gene.total_fitness - result);

		if (new_gene.fitness == 1)
		{
			cout << "a = " << new_gene.alleles[0];
			cout << "b = " << new_gene.alleles[1];
			cout << "c = " << new_gene.alleles[2];
			cout << "d = " << new_gene.alleles[3];
		}
	}

	void Calculate_chance_for_conieving()  
	{
		float total_revert_coeficients_for_fitness=0;

		for (int i = 0; i < population_size; i++)
		{
			total_revert_coeficients_for_fitness += population[i].fitness;
		}

		for (int i = 0; i < population_size; i++)
		{
			population[i].chance_for_conceiving = population[i].fitness / total_revert_coeficients_for_fitness *100;
		}
	}

	void Create_new_generation_roulette(int parent_1, int parent_2)
	{
		int crossover;
		int index_for_child;
		crossover = rand() % 4;

		index_for_child = Killing_unluckers();

		for (int i = 0; i < crossover; i++)
		{
			population[index_for_child].alleles[i] = population[parent_1].alleles[i];
		}

		for (int i = crossover; i < 4; i++)
		{
			population[index_for_child].alleles[i] = population[parent_2].alleles[i];
		}

		for (int i = 0; i < rand() % 4; i++)
		{
			if (rand() % 100 < 1)
			{
				Mutate(index_for_child, i);
			}
		}

		Calculate_fiteness_for_unite(population[index_for_child]);


	}

	void Create_new_generation_tournament(int parent_1, int parent_2, int index_of_weakest)
	{
		int crossover;
		int index_for_child;
		crossover = rand() % 3+1;
		
		index_for_child = index_of_weakest;

		for (int i = 0; i < crossover;i++)
		{
			population[index_for_child].alleles[i] = population[parent_1].alleles[i];
		}

		for (int i = crossover; i < 4; i++)
		{
			population[index_for_child].alleles[i] = population[parent_2].alleles[i];
		}

		if (rand() % 100 < 1)
		{
		//	for (int i = 0; i < rand() % 4; i++)
			{
					Mutate(index_for_child, rand()%4);
			}
		}
		Calculate_fiteness_for_unite(population[index_for_child]);


	}

	int Killing_unluckers()
	{
		int loser;
		loser = rand() % population_size;
		return loser;
	}

	int Weakest()
	{
		int index_of_weakest=0;
		for (int i = 0; i < population_size; i++)
		{
			if (population[index_of_weakest].chance_for_conceiving>population[i].chance_for_conceiving)
			{
				index_of_weakest = i;
			}
		}
		return index_of_weakest;
	}

	void Roulette()
	{
		int parent_1, parent_2;
		for (int i = 0; i < (rand() % (population_size*population_size)); i++)
		{
			parent_1 = rand() % population_size ;
			parent_2 = rand() % population_size ;

			if (parent_1 != parent_2)
			{
				Create_new_generation_roulette(parent_1, parent_2);
			}
			else
			{

			}
		}

	}

	void Tournament()
	{
		int qwe = rand() % (population_size*population_size);
		int parent_1, parent_2;
		for (int i = 0; i < (rand() % (population_size*population_size)); i++)
		{
			int index_of_weakest = Weakest();
			parent_1 = rand() % population_size;
			parent_2 = rand() % population_size;
			if ((parent_1 != parent_2) && (parent_1 != index_of_weakest) && (parent_2 != index_of_weakest)) //zapret na skrewivenie slabeiwim
			{
				Create_new_generation_tournament(parent_1, parent_2,index_of_weakest);
			}
			else
			{

			}
		}
		

	}

	void Mutate(int index_of_child,int mutate_allele)
	{
		population[index_of_child].alleles[mutate_allele] = rand() % 100;
	}

	void Solve()
	{
		srand((unsigned)time(NULL));

		Create_first_generation();
		Calculate_fiteness_for_population();
		Calculate_chance_for_conieving();
		//Roulette();
		for (int i = 0; i < 400; i++)
		{
			Tournament();
		}
		


	}

};

