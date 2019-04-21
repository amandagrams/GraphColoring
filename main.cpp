#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

#include <random>

using namespace std;

#define FIM "\e[0m"
#define AZUL "\e[44m"
#define VERMELHO "\e[45m"
#define VERDE "\e[42m"

#include "include/ag.h"

class Grafo
{
private:
    vector<vector<unsigned int>> grafo;
    unsigned int n_nos, n_arestas;

public:
    bool loadgrafo(string nome_grafo)
    {
        string file_path = "entradas/";
        file_path += nome_grafo + ".txt"; // Armazena o caminho do texto simples

        ifstream grafo_simples(file_path);

        if (grafo_simples.fail())
            throw("Caminho Incorreto");

        string input;
        grafo_simples >> input;
        while (input != "p")
            grafo_simples >> input;

        grafo_simples >> n_nos >> n_arestas;

        unsigned int no1, no2;

        /* Agora sabemos o número de nós, então
         nós redimensionamos o gráfico para alocar todos */
        grafo.resize(n_nos);

        /* Define o último nó, vamos usar essa variável para saber
         quando estamos carregando as bordas de um nó diferente,
         a fim de inseri-lo no vetor*/

        while (!grafo_simples.eof())
        {

            /* Carregando os valores em variáveis */
            grafo_simples >> no1 >> no2;
            grafo[no1 - 1].push_back(no2 - 1);
        }
        grafo_simples.close();
        return true;
    }

    void printGrafo()
    {
        if (!(grafo.size() > 0))
        {
            cout << "O grafo não foi carregado.";
        }
        else
        {
            for (size_t i = 0; i < grafo.size(); i++)
            {
                cout << endl
                     << AZUL << "[" << i << "]" << FIM << "->";
                for (size_t j = 0; j < grafo[i].size(); j++)
                {
                    cout << " " << grafo[i][j];
                }
            }
            cout << endl;
        }
    }

    unsigned int getNos()
    {
        return this->n_nos;
    }
    unsigned int getArestas()
    {
        return this->n_arestas;
    }

    vector<vector<unsigned int>> getGrafo()
    {
        return this->grafo;
    }
};

int main(int argc, char *argv[])
{

    /*Aqui armazenamos os nomes das instancias */

    vector<string> data = {"anna.col", "games120.col", "myciel6.col"};
    Grafo grafo_principal;

    unsigned int n_grafo;

    if (argc < 2)
    {
        cout << "Selecione uma instância: " << endl;
        for (size_t i = 0; i < data.size(); i++)
        {
            cout << " [" << i << "] " << data[i] << endl;
        }
        cout << "Digite um Número: ";
        cin >> n_grafo;
    }
    else if (argc > 2)
    {
        cout << "Muitos argumentos." << endl;
        return 0;
    }
    else if (argc == 2)
    {
        n_grafo = atoi(argv[1]);
    }

    /*Verifica se o número do grafo é válido*/
    if (n_grafo >= data.size())
    {
        cout << "Este grafo não é válido" << endl;
    }
    else
    {
        bool error = grafo_principal.loadgrafo(data[n_grafo]);
        if (!error)
        {
            cout << "O grafo não pode ser carregado." << endl;
            return 0;
        }
        else
        {
            cout << "Grafo carregado com sucesso." << endl;
        }
    }
    grafo_principal.printGrafo();

    struct timespec t_antes, t_depois;
    long tempo_total = 0;
    clock_gettime(CLOCK_MONOTONIC, &t_antes);

    unsigned int total_iteracoes = 0, max_iteracoes = 100000;

    max_iteracoes = 100000;
    int n_individuos = 20;
    double p_melhor = 40.0, p_cross = 40.0, p_mutacao = 20.0;
    int min_cores = 0;
    cout << VERMELHO << "\n\n\n\n========================================" << endl;
    cout << VERMELHO << "  ALGORITMO GENÉTICO - RODANDO SOLUÇÃO " << endl;
    cout << VERMELHO << "========================================\n\n\n\n"
         << FIM << endl;

    AG AG_Solucao(n_individuos, grafo_principal.getNos(), grafo_principal.getArestas(), grafo_principal.getGrafo());
    AG_Solucao.MainLoop(max_iteracoes, total_iteracoes, p_melhor, p_cross, p_mutacao, min_cores);
    AG_Solucao.printPopulacao();

    clock_gettime(CLOCK_MONOTONIC, &t_antes);
    tempo_total = t_antes.tv_nsec - t_depois.tv_nsec;

    cout << AZUL << "\n\nEncontrei a solução em " << tempo_total << " nano segundos." << endl;
    cout << "e " << total_iteracoes << " iterações." << FIM << endl;
}