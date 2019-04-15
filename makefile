principal:
	g++ main.cpp ag.cpp individuo.cpp -o bin/main
	@	 echo ">> Compilado com sucesso."

clean: 
	rm bin/main
	@   echo ">> Erro na compilação."
