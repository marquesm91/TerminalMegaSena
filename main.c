#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int geraNumero(int inicio, int final) {
	int random_number = rand(); // entre 1 e RAND_MAX (constante stdlib.h)

	// Alterando o range para [1,final) de random_number
	random_number = random_number % final;  // [1,60)

	// Alterando o range para [inicio + 1, inicio + final) ou [inicio + 1, inicio + final - 1] de random_number 
	random_number = random_number + inicio - 1; // [1,60]

	return random_number;
}

int main ()
{
	FILE *f = fopen("resultados.csv", "w+t");

	srand (time(NULL)); // Gerando seed para numeros randomicos

	int listaNumeros[60];
	int inicio = 1;
	int final = 60;

	// Zerando valores do vetor
	for (int i = 0; i < 60; i++){
		listaNumeros[i] = 0;
	}

	// Gerando 3000 numeros aleatorios entre 1 e 60 e salvando suas ocorrencias
	for (int i = 0; i < 3000; i++){
		int index = geraNumero(inicio, final);
		listaNumeros[index]++;
	}

	// Imprimindo resultados
	fprintf(f,"NUMERO;OCORRENCIAS\n");
	for (int i = 0; i < 60; i++){
		printf("o numero %d foi sorteado %d vezes\n", i+1, listaNumeros[i]);
		fprintf(f,"%d;%d\n", i+1, listaNumeros[i]);
	}

	fclose(f);
	return 0;
}