#include "include/individuo.h"

Individuo ::Individuo(unsigned int n_genes)
{
    this->n_genes = n_genes;

    int random;
    unsigned int cor = 0;

    for (unsigned int i = 0; i < n_genes; i++)
    {
        random = this->getRandom(0.0, n_genes);

        if (random == 0 || i == 0)
            cromossomo.push_back(cor);
        else
        {
            cor++;
            cromossomo.push_back(cor);
        }
    }
};

Individuo::Individuo(vector<unsigned int> cromossomo)
{
    this->cromossomo = cromossomo;
    this->n_genes = cromossomo.size();
};

unsigned int Individuo::getNumCores()
{
    set<int> cores_distintas;

    for (auto curr_int = cromossomo.begin(), end = cromossomo.end(); curr_int != end; ++curr_int)
    {
        cores_distintas.insert(*curr_int);
    }

    return cores_distintas.size();
};

void Individuo::printCromossomo()
{

    for (unsigned int i = 0; i < cromossomo.size(); i++)
    {
        cout << VERDE << PRETO << " " << this->cromossomo[i] << FIM;
    }
    cout << " \n\n Número de cores usadas: " << this->getNumCores() << endl;
};

unsigned int Individuo::at(unsigned int i)
{
    return this->cromossomo[i];
};

void Individuo::setFitness(unsigned int fitness)
{
    this->fitness = fitness;
};

unsigned int Individuo::getFitness()
{
    return this->fitness;
};

void Individuo::mutate()
{
    this->fitness = 0;
    double max_iteracoes = n_genes / 2;

   
    unsigned int random_a = this->getRandom(1.0, max_iteracoes);
    unsigned int random_b;
    

    for (unsigned int i = 0; i < random_a; i++)
    {
        random_b = this->getRandom(0.0, n_genes - 1);
        replace(cromossomo.begin(), cromossomo.end(), cromossomo[random_b], cromossomo[(random_b + i + random_a) % n_genes]);
    }
};

Individuo Individuo::reproduzir(Individuo parent_2)
{

    double inicio = n_genes / 3;
    unsigned int random_a = this->getRandom(inicio, n_genes);

    vector<unsigned int> novo_individuo_chr = this->cromossomo;

    for (unsigned int i = random_a; i < n_genes; i++)
    {
        novo_individuo_chr[i] = parent_2.at(i);
    }

    Individuo new_ind(novo_individuo_chr);
    return new_ind;
};

void Individuo::insertCor(int p, int c)
{
    cromossomo[p] = c;
};
