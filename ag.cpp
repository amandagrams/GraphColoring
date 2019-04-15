#include "include/ag.h"

    AG::AG(unsigned int n_individuos, unsigned int n_genes, unsigned int n_arestas, vector<vector<unsigned int>> grafo_principal){
        this->n_individuos = n_individuos;
        this->n_genes = n_genes;
        this->n_arestas = n_arestas;
        this->grafo_principal = grafo_principal;

        for(unsigned int i = 0; i < n_individuos; i++){

            Individuo a(n_genes);
            populacao.push_back(a);
        }

    };

    AG::AG(unsigned int n_genes, unsigned int n_arestas, vector<vector<unsigned int>> grafo_principal){
        this->n_genes = n_genes;
        this->n_arestas = n_arestas;
        this->grafo_principal = grafo_principal;
        this->n_individuos = 0;
    }


    void AG::addIndividuo(Individuo ind_new){
        this->populacao.push_back(ind_new);
        n_individuos++;
    };

    vector<Individuo> AG::BuscaMelhorIndividuo( double porcentagem){
        
        vector<Individuo> melhores_individuos;

        //pair< Fitness value, index in the populacao>
        priority_queue< pair<unsigned int, int>> melhor_ind;

        /*  To have the best n_melhores_individuos, we insert the elements
            into a queue and then pop just what we need.
            (It can be done more efficient, if we don't push the individuals
            smaller than the last element of the queue but back() is not working
            for some reason, I will improve this if I have time)
        */

        for (unsigned int i = 0; i < n_individuos; ++i) {
    
            melhor_ind.push(std::pair<unsigned int, int>(fitnessDoIndividuo(i), i));
        }

        //Number of individuals that we will choose
        int n_melhores_individuos = porcentagem*n_individuos;


        /*  Here we pop the elements that we want
        */
        for (int i = 0; i < n_melhores_individuos; ++i) {
            int ki = melhor_ind.top().second;

            melhores_individuos.push_back(this->populacao[ki]);
            
            melhor_ind.pop();
        }

        return melhores_individuos;
    };

    vector<Individuo> AG::Reproduzir(vector<Individuo> populacao, unsigned int novo_ind){
        vector<Individuo> nova_populacao;
        unsigned int parente_1, parente_2;
        Individuo son(n_genes);
        unsigned int n_individuos = populacao.size();
        

        for(unsigned int i = 0; i < novo_ind;i++){
            parente_1 = getRandom(0, n_individuos);
        
            //This way we won't have parente_1 == parente_2
            parente_2 = (parente_1 + (int)getRandom(1, n_individuos - 1))  % n_individuos;
            //cout << "parent 1: " << parente_1 << ", parent 2: " << parente_2 << endl;

            son = populacao[parente_1].reproduzir(populacao[parente_2]);
            nova_populacao.push_back( son );

        }
        return nova_populacao;
    }

    vector<Individuo> AG::Mutacao(vector<Individuo> populacao, unsigned int novo_ind){
        vector<Individuo> nova_populacao;
        unsigned int random_idx;

        for(unsigned int i = 0; i < novo_ind; i++){
            random_idx = getRandom(0, populacao.size());

            Individuo novo_individuo = populacao[random_idx];
            novo_individuo.mutate();
            nova_populacao.push_back(novo_individuo);
        }
        return nova_populacao;
    }


    void AG::CriaNovaPopulacao(double p_melhor, double p_reproduzir, double p_mutacoes){
        double p_total = p_melhor + p_reproduzir + p_mutacoes;
        
        p_melhor = p_melhor / p_total;
        double n_reproduzir = n_individuos * (p_reproduzir / p_total);
        double n_mutacoes = n_individuos * (p_mutacoes / p_total);
        vector<Individuo> nova_populacao;
        
        nova_populacao = BuscaMelhorIndividuo(p_melhor);
        
        vector<Individuo> reproduzir_v = Reproduzir(nova_populacao, n_reproduzir);
        vector<Individuo> mutacao_v = Mutacao(nova_populacao, n_mutacoes);
        
        //Insert the reproduce and mutate vector into the new populacao.
        
        nova_populacao.insert(end(nova_populacao), begin(reproduzir_v), end(reproduzir_v));
        
        nova_populacao.insert(end(nova_populacao), begin(mutacao_v), end(mutacao_v));


        this->populacao = nova_populacao;
    }


    unsigned int AG::fitnessDoIndividuo(unsigned int index){
        
        unsigned int fit = 0;
        //If we calculate it previously we dont need to do it again
        if(populacao[index].getFitness() != 0){
            fit = populacao[index].getFitness();
        }
        else{
            
            for(unsigned int i = 0; i < n_genes; i++){
                //cout << endl <<"i=" << i << "-  ";
                for(unsigned int j = 0; j < grafo_principal[i].size(); j++){
                    unsigned int cmp_number = populacao[index].at( grafo_principal[i][j] );
                    //cout << populacao[index].at(i)<<","<< cmp_number << " " ;
                    if(populacao[index].at(i) != cmp_number){
                        fit++;
                    //    cout << "1 ";
                    }
                }

            }
            if(fit == n_arestas)
                fit += (n_genes - populacao[index].getNumCores());
            

            populacao[index].setFitness(fit);
        }
    return fit;
    };

    void AG::printPopulacao(){
        for(unsigned int i = 0; i < n_individuos; i++){
            cout << endl;
            populacao[i].printCromossomo();
            cout << "Fitness: " << fitnessDoIndividuo(i) ;
        }


    };

    bool AG::CorCorreta(unsigned int n_cores, double porcentagem){
        int avg = 0;
        bool terminar = false;
        double per = n_individuos * (porcentagem/100);

        for(unsigned int i = 0; i < populacao.size() && !terminar; i++){
            if(populacao[i].getNumCores() == n_cores){
                avg++;
                if(avg == per)
                    terminar = true;
            }
        }

        return terminar;
    };


    void AG::MainLoop(unsigned int max_iteracoes,unsigned int &total_iteracoes,double p_melhor,double p_cross,double p_mutacao, int min_colors){
        bool cor_color = false;
        cout << endl;
        int j=0;
        for(total_iteracoes = 0; total_iteracoes < max_iteracoes && !cor_color; total_iteracoes++){
            cout << "NOVA POPULAÇÃO na iteração " << j << ":" << endl;
            this->CriaNovaPopulacao( 40.0, 40.0, 20.0);
            if(this->CorCorreta(min_colors,100.0 - p_mutacao)){
                cor_color = true;
            }
            j++;
        }

    }