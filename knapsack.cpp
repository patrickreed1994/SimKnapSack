#include <stdlib.h>
#include <iostream>
using namespace std;

const int BOXNUM = 50;
const int SURVIVORS = 20;
const int INITIAL_POPULATION = 40;
const int BREEDRATE = 2;
const int GENERATIONS = 100;
const int DOMUTATERATE = 5;		//5 of 100
const int MUTATIONRATE = 3; 		//3 of 100

class Box
{
public:
	int value;
	int weight;
	Box();
};

class DNA
{
public:
	bool boxes[50];

	DNA();
	int getValue();
	int getWeight();
};

Box* box[BOXNUM];	//array of boxes

DNA* dna[2*SURVIVORS*(SURVIVORS+1)];	//population
int population=0;	//population: how many dnas

Box::Box()
{

	//STEP 0
	value = rand() % 100 + 1;
	weight = rand() % 50 + 1;
}

DNA::DNA()
{
	//for i in 50
	for(int i = 0; i < BOXNUM; i++)
	{
		boxes[i] = rand()%2==1;
	}
}

int DNA::getWeight()
{
	//sum up the weights & return it
	int sum=0;
	for(int i=0; i<BOXNUM;i++)
	{
		if(box[i])
		{
			sum+=box[i]->weight;
		}
	}
	return sum;
}

int DNA::getValue()
{
	int sum=0;
	for(int i=0; i<BOXNUM;i++)
	{
		if(box[i])
			sum+=box[i]->value;
	}
	return sum;
}

main()
{
	//STEP 0
	//make my boxes
	//for i in 50, new Box()
	
	for(int i = 0; i < BOXNUM; i++)
	{
		box[i]=new Box();
		cout<<"Box "<<i<<": w="<<box[i]->weight<<", v="<<box[i]->value<<endl;
	}
	
	//while our population is less than initial population
	//	dna[i]=new DNA()
	// 	only add it if the weight below 1000

	while(population > INITIAL_POPULATION)
	{
		DNA* d = new DNA();
		if(d->getWeight()<=1000)
		{
			dna[population]=d;	
			population++;
		}
	}

	

	//for loop # of generations
	//	figure out who the best is and print out its dna/weight/value
	//	kill
	for(int j =0; j<population; j++)
	{
		for(int k =0; k<population - 1; k++)
		{
			if(dna[k+1]->getValue() > dna[k]->getValue())
			{
				DNA* temp = dna[k+1];
				dna[k+1] = dna[k];					
				dna[k] = temp;
			}
		}
	}
	cout << "DNA 0 has "<< dna[0]->getWeight() << " "<<dna[0]->getValue()<<endl;
	cout << "DNA 1 has "<< dna[1]->getWeight() << " "<<dna[1]->getValue()<<endl;
	cout << "DNA 2 has "<< dna[2]->getWeight() << " "<<dna[2]->getValue()<<endl;
	
	//set population = SURVIVORS
	//	breed
	
	//go through every possible pair
	int breedpop = population;
	for(int gen = 0; gen < GENERATIONS; gen++)
	{
		for(int dad = 0; dad<breedpop; dad++)
		{
			for(int mom=0; mom<breedpop; mom++)
			{
				//don't breed with yourself
				if(mom != dad) continue;

				//20% chane of mate
				if (rand() % 10<=BREEDRATE) continue;

				//twisty point
				int crossoverpoint = rand()%BOXNUM;
			
				DNA* baby = new DNA();
				//copy stuff over dad
				for(int i=0; i<crossoverpoint; i++)
				{
					baby->boxes[i] = dna[dad]->boxes[i];
				}
				//copy stuff over mom
				for(int j=crossoverpoint; j<BOXNUM; j++)
				{
					baby->boxes[j] = dna[mom]->boxes[j];
				}
		
				//keep the baby
				if (baby->getWeight() > 1000)
					continue;
				//TODO: garbage collect the baby

				dna[population++] = baby;

			}
		}

	//	mutate
	
	int cloningpop = population;

	// 1) for each dna
	for(int i = 0; i< cloningpop; i++)
	{
		// 2) clone with 5%
		if (rand()%100 < DOMUTATERATE)
		{
			// 3) make a new one
			DNA* mutant = new DNA();
			for(int j = 0; j < BOXNUM; j++)
			{
				// 4) for loop, copy boxes over
				mutant->boxes[j] = dna[i]->boxes[j];
			}
			
			cout<< "Making a clone: parent: "<<dna[i]->getValue() <<" spawn: "<<mutant->getValue() << endl;
		
			// 5) for each box
			for (int k = 0; k < BOXNUM; k++)
			{
				//6. decide to change with 3% probability
				if(rand()%100 < MUTATIONRATE)
				{
					// 7) flip it t->f or f->t
					mutant->boxes[k] = !mutant->boxes[k];
				}
			}
			// 8) add to pop only if valid weight
			if(mutant->getWeight() > 1000)
				dna[population++] = mutant;
			//TODO: garbage collect the mutant
		}
	}
	
	
	
	}
	
	
	// 9) print value of parent
	// 10) print value of mutant
	

}
