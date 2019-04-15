#include <vector>
#include <stdlib.h>
#include <time.h>
#include <queue>

#include "individuo.h"
using namespace std;

class AG
{
private:
    //População atual
    vector<Individuo> populacao;

    // Número de indivíduos na população
    unsigned int n_individuos;
    // Número de genes no gráfico (nós)
    unsigned int n_genes;
    // Número de arestas no gráfico
    unsigned int n_arestas;
    // O grafo que está sendo usado
    vector<vector<unsigned int>> grafo_principal;

public:
    /*  It will initialize the populacao with a n_individuos number of individuals
            All individuals will be intilized with random values
            n_genes is the number of nodes in the graph
        */
    AG(unsigned int n_individuos, unsigned int n_genes, unsigned int n_arestas, vector<vector<unsigned int>> grafo_principal);

    /*  Initialize a AG without a populacao
        */
    AG(unsigned int n_genes, unsigned int n_arestas, vector<vector<unsigned int>> grafo_principal);

    /*  Add a new individual to the populacao
            ind_novo: New individual
        */
    void addIndividuo(Individuo ind_novo);

    /*  It will find the bests Individuals of the current populacao
            Percentage of Indiviuals that will return:
                From 0 to 1
            return: Bests p% Individuals
        */
    vector<Individuo> BuscaMelhorIndividuo(double porcentagem);

    /*  Will generate a new populacao based on a previous one, using the reproduce method
            and the number of individuals that we want
            populacao: previous populacao
            novo_individuo: numbwe of individuals in the new populacao

            return: the new populacao
        */
    vector<Individuo> Reproduzir(vector<Individuo> populacao, unsigned int novo_individuo);

    /*  Will generate a new populacao based on a previous one, using the mutate method
            and the number of individuals that we want
            populacao: previous populacao
            novo: numbwe of individuals in the new populacao

            return: the new populacao
        */
    vector<Individuo> Mutacao(vector<Individuo> populacao, unsigned int novo_individuo);

    /*  It will create a new populacao
                p_melhor: A porcentagem will remain from the previous populacao. (Best Individuals)
                p_reproduzir: A porcentagem will be created with 2 parents.
                p_mutatuions: A porcentagem will be mutations. 
        */
    void CriaNovaPopulacao(double p_melhor, double p_reproduzir, double p_mutacoes);

    /*  Method that will return a bool if there was a problem running the Genetic Algorithm
            It will write in melhor_individuo, the best result it could find
        */
    bool CalcularGA(Individuo &melhor_individuo);

    /*  It will return an int with the value of the fitness of the Individuo
            This value is calcuflated:
                1. Every time a edge is good (both nodes have different colours)
                    it will add 1 to the variable, if the node is not correct wilk add 0.

                2. If all the edges are correct (fitnes = N_edges) it will add  
                    N-N_colours_used to the value.
            
            Return: Fitness of a specific infividual
        */
    unsigned int fitnessDoIndividuo(unsigned int index);

    /*  Print the populacao and the values of the Individuals
        */
    void printPopulacao();

    /*  It will check if the "porcentagem" of the populacao has found a
            solution with "n_cores"

                n_cores: The number of colours that will use as a reference
                porcentagem: The porcentagem of the populacao that has to found a 
                    solution with that number of colours
            return: true if all of that individuals have a solution with that n_cores 
        */
    bool CorCorreta(unsigned int n_cores, double porcentagem);

    /*  Main Loop for the Genetic Algorithm system
                max_iteracoes: maximum number of iteration before the program stops
                total_iteration: the real total iteration that the program made
                p_melhor: Percentage of the best individuals that will be used to create a new populacao
                p_cross: porcentagem of the new individuals that will be created reproducing other individuals
                p_mutacao: Percentage of the new individuals that will be created with mutations
                min_cores: minimum amount of colors needed to solve the problem (if unknown "min_cores = 0" )
        */
    void MainLoop(unsigned int max_iteracoes, unsigned int &total_iteracoes, double p_melhor, double p_cross, double p_mutacao, int min_cores);

    /*  Test method to mutate all the individuals of a populacao (just for fun)
        */
    void mutateAll()
    {
        for (unsigned int i = 0; i < n_individuos; i++)
        {
            populacao[i].mutate();
        }
    }

    /*  It will return a random number between inicio and fim
        */
    double getRandom(double inicio, double fim)
    {
        random_device rd;
        mt19937 mt(rd());
        uniform_real_distribution<double> dist(inicio, fim);
        return dist(mt);
    }

    /*  It will add the number of colors being used in each individual in the populacao
        */
    void CoresPorIndividuo(vector<vector<unsigned int>> &cores_antigas)
    {

        for (unsigned int i = 0; i < n_individuos; i++)
        {
            cores_antigas[i].push_back(populacao[i].getNumCores());
        }
    };
};