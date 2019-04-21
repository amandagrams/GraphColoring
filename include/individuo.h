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


class Individuo
{
private:
    vector<unsigned int> cromossomo;
    unsigned int n_genes;
    unsigned int N_colours_used = 0;
    unsigned int fitness = 0;

public:
    Individuo(){};

   
    Individuo(unsigned int n_genes);

   
    Individuo(vector<unsigned int> cromossomo);

    unsigned int getNumCores();

  
    void printCromossomo();

   
    unsigned int at(unsigned int i);

    
    void setFitness(unsigned int fitness);

   
    unsigned int getFitness();

    
    void mutate();

    
    Individuo reproduzir(Individuo parent_2);

   
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