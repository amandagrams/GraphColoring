#ifndef INDIVIDUO_H
#define INDIVIDUO_H

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <random>
#include <algorithm>
#include <set>

#define FIM "\e[0m"
#define AZUL "\e[44m"
#define VERMELHO "\e[45m"
#define VERDE "\e[42m"
#define PRETO "\e[30m"

using namespace std;

/*
The Individuo class is used in the Genetic Algorithm and in the Simulated Annealing
algorithm because the implementation and some methods are useful 
but the usage is different.
The fitness is for the GA but in SA it is used as the cost
*/
class Individuo
{
private:
    vector<unsigned int> cromossomo;
    unsigned int n_genes;
    unsigned int N_colours_used = 0;
    unsigned int fitness = 0;

public:
    Individuo(){};

    /*  Initialize a certain individual with random values, 
            and n_genes number of genes
        */
    Individuo(unsigned int n_genes);

    /*  Create an individual with a given cromossomo and the number of colours used
        */
    Individuo(vector<unsigned int> cromossomo);

    /*  Numer of differents colours used in this result
        */
    unsigned int getNumCores();

    /*  Print the Chromosome and its colours 
        */
    void printCromossomo();

    /*  It will return the value of the cromossomo at the i position
        */
    unsigned int at(unsigned int i);

    /*  Assign a value to the fitness
        */
    void setFitness(unsigned int fitness);

    /*  Return the fitness of the individual
        */
    unsigned int getFitness();

    /*  It will mutate the individual
        */
    void mutate();

    /*  Will create a new Individuo based on his parents
            Parent 1 will be the Individuo that has been instatiated.
            parent_2: The second parent
            It will create a random number that will be the
                percentage used from the parent 1 
                (1-p will be the percentage used from parent_2)
            return: The new individual
        */
    Individuo reproduzir(Individuo parent_2);

    /*  Insert a color c 
            in a certain position p
        */
    void insertCor(int p, int c);

    double getRandom(double inicio, double fim)
    {
        random_device rd;
        mt19937 mt(rd());
        uniform_real_distribution<double> dist(inicio, fim);
        return dist(mt);
    }
};

#endif