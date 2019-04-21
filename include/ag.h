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
   
    AG(unsigned int n_individuos, unsigned int n_genes, unsigned int n_arestas, vector<vector<unsigned int>> grafo_principal);


    AG(unsigned int n_genes, unsigned int n_arestas, vector<vector<unsigned int>> grafo_principal);

    
    void addIndividuo(Individuo ind_novo);

   
    vector<Individuo> BuscaMelhorIndividuo(double porcentagem);

   
    vector<Individuo> Reproduzir(vector<Individuo> populacao, unsigned int novo_individuo);

  
    vector<Individuo> Mutacao(vector<Individuo> populacao, unsigned int novo_individuo);

 
    void CriaNovaPopulacao(double p_melhor, double p_reproduzir, double p_mutacoes);

   
    bool CalcularGA(Individuo &melhor_individuo);

    unsigned int fitnessDoIndividuo(unsigned int index);

    
    void printPopulacao();

    bool CorCorreta(unsigned int n_cores, double porcentagem);

    void MainLoop(unsigned int max_iteracoes, unsigned int &total_iteracoes, double p_melhor, double p_cross, double p_mutacao, int min_cores);

    void mutateAll()
    {
        for (unsigned int i = 0; i < n_individuos; i++)
        {
            populacao[i].mutate();
        }
    }

    double getRandom(double inicio, double fim)
    {
        random_device rd;
        mt19937 mt(rd());
        uniform_real_distribution<double> dist(inicio, fim);
        return dist(mt);
    }

    void CoresPorIndividuo(vector<vector<unsigned int>> &cores_antigas)
    {

        for (unsigned int i = 0; i < n_individuos; i++)
        {
            cores_antigas[i].push_back(populacao[i].getNumCores());
        }
    };
};