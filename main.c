#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_SORTEIO 6
#define TOTAL_NUM 60
#define TOTAL_SORTEIO 3000

struct Lista_numeros{
	int numero;
	int ocorrencias; // Quantas vezes ele apareceu nos sorteios
	int ultimo_sorteio; // Ultima vez que apareceu nos sorteios
};

void imprime_sorteio(int sorteio[]) {
	for (int j = 0; j < TAM_SORTEIO; j++){
		if(j < TAM_SORTEIO - 1)
			printf("%d - ", sorteio[j]);
		else
			printf("%d", sorteio[j]);
	}
	printf("\n");
}

// Ordena numeros do sorteio na ordem crescente
void ordena_sorteio(int sorteio[]){   
	for(int i = 0; i < TAM_SORTEIO; i++){ 
		for(int j = i + 1; j < TAM_SORTEIO; j++) {
			if(sorteio[i] > sorteio[j]){ 
				int aux = sorteio[i]; 
				sorteio[i] = sorteio[j]; 
				sorteio[j] = aux; 
      		}
		}
  	} 
}

// Ordena lista baseado nas ocorrencias de cada numero na ordem crescente
void ordena_lista(struct Lista_numeros lista_numeros[]) {
	for(int i = 0; i < TOTAL_NUM; i++){ 
		for(int j = i + 1; j < TOTAL_NUM; j++) {
			if(lista_numeros[i].ocorrencias > lista_numeros[j].ocorrencias){ 
				struct Lista_numeros aux = lista_numeros[i]; 
				lista_numeros[i] = lista_numeros[j]; 
				lista_numeros[j] = aux; 
      		}
		}
  	}
}


int gera_numero(int inicio, int final) {
	int numero = rand(); // entre 0 e RAND_MAX (constante stdlib.h)

	// Alterando o range para [0,final) de numero
	numero = numero % final;  // [1,60)

	// Alterando o range para [inicio, inicio + final) ou [inicio, inicio + final - 1] de numero 
	numero = numero + inicio; // [1,61) ou [1,60]

	return numero;
}

int gera_sorteio(int inicio, int final, int sorteio[], struct Lista_numeros lista_numeros[]){
	
	int numero = gera_numero(inicio, final);
	sorteio[0] = numero;

	// Gerar TAM_SORTEIO numeros sempre diferentes
	for(int i = 1; i < TAM_SORTEIO; i++){
		sorteio[i] = gera_numero(inicio, final);
		for(int j = i - 1; j >= 0; j--) {
			if (sorteio[j] == sorteio[i]) {
				sorteio[i] = gera_numero(inicio, final);
				j = i - 1;
			}
		}
		lista_numeros[sorteio[i]-1].ocorrencias++;
	}
	return 0;
}

int main ()
{
	FILE *arquivo = fopen("resultados.csv", "w+t");

	if (!arquivo) {
		printf("Nao foi possivel abrir o arquivo resultados.csv para escrita.");
		exit(-1);
	}

	srand (time(NULL)); // Gerando seed para numeros randomicos
	struct Lista_numeros lista_numeros[TOTAL_NUM];
	int sorteios[TOTAL_SORTEIO][TAM_SORTEIO]; // TOTAL_SORTEIO sorteios de 6 numeros cada um
	int inicio = 1;
	int final = TOTAL_NUM;

	// Zerando valores da estrutura Lista_numeros
	for (int i = 0; i < TOTAL_NUM; i++){
		lista_numeros[i].numero = i + 1;
		lista_numeros[i].ocorrencias = 0;
		lista_numeros[i].ultimo_sorteio = 0;
	}

	// Zerando valores da estrutura Lista_numeros
	for(int i = 0; i < TOTAL_SORTEIO; i++){
		for (int j = 0; j < TAM_SORTEIO; j++){
			sorteios[i][j] = 0;
		}
	}

	// Gerando 3000 numeros aleatorios entre 1 e 60 e salvando suas ocorrencias
	for (int i = 0; i < TOTAL_SORTEIO; i++){
		gera_sorteio(inicio, final, sorteios[i], lista_numeros);
		ordena_sorteio(sorteios[i]);
		printf("Sorteio[%d] = ", i+1); imprime_sorteio(sorteios[i]);
	}

	// Imprimindo ocorrencias de cada numero de maneira ordenada
	ordena_lista(lista_numeros);
	fprintf(arquivo,"NUMERO;OCORRENCIAS\n");
	for (int i = 0; i < TOTAL_NUM; i++){
		printf("o numero %d foi sorteado %d vezes\n", lista_numeros[i].numero, lista_numeros[i].ocorrencias);
		fprintf(arquivo,"%d;%d\n", lista_numeros[i].numero, lista_numeros[i].ocorrencias);
	}

	fclose(arquivo);
	return 0;
}