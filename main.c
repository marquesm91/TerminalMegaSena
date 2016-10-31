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

struct Melhores {
	int numero1;
	int numero2;
	int ocorrencias;
};

int gera_numero(int inicio, int final) {
	int numero = rand(); // entre 0 e RAND_MAX (constante stdlib.h)

	// Alterando o range para [0,final) de numero
	numero = numero % final;  // [1,60)

	// Alterando o range para [inicio, inicio + final) ou [inicio, inicio + final - 1] de numero 
	numero = numero + inicio; // [1,61) ou [1,60]

	return numero;
}

void imprime_sorteio(int sorteio[]) {
	for (int j = 0; j < TAM_SORTEIO; j++){
		if(j < TAM_SORTEIO - 1)
			printf("%d - ", sorteio[j]);
		else
			printf("%d", sorteio[j]);
	}
	printf("\n");
}

void imprime_lista_numeros(struct Lista_numeros lista_numeros[], int tam) {
	
	struct Lista_numeros aux_lista[TOTAL_NUM];

	for(int i = 0; i < TOTAL_NUM; i++)
	{
		aux_lista[i] = lista_numeros[i];
	}

	for(int i = 0; i < tam; i++){ 
		for(int j = i + 1; j < tam; j++) {
			if(aux_lista[i].numero > aux_lista[j].numero){ 
				struct Lista_numeros aux = aux_lista[i]; 
				aux_lista[i] = aux_lista[j]; 
				aux_lista[j] = aux; 
      		}
		}
		printf("o numero %d foi sorteado %d vezes\n", aux_lista[i].numero, aux_lista[i].ocorrencias);
  	}
}

void imprime_melhores_duplas(struct Melhores *melhores, int tam) {
	for(int i = 0; i < tam; i++)
	{
		printf("A dupla <%d", melhores[i].numero1);
		printf(",%d> ", melhores[i].numero2);
		printf("ocorreu %d vezes\n", melhores[i].ocorrencias);
	}
}

// Ordena numeros do sorteio na ordem crescente
void ordena_lista_imprime(int sorteio[]) {
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

// Ordena numeros do sorteio na ordem crescente
void ordena_sorteio(int sorteio[]) {
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
void ordena_lista_numeros(struct Lista_numeros lista_numeros[]) {
	for(int i = 0; i < TOTAL_NUM; i++){ 
		for(int j = i + 1; j < TOTAL_NUM; j++) {
			if(lista_numeros[i].ocorrencias < lista_numeros[j].ocorrencias){ 
				struct Lista_numeros aux = lista_numeros[i]; 
				lista_numeros[i] = lista_numeros[j]; 
				lista_numeros[j] = aux; 
      		}
		}
  	}
}

// Ordena lista baseado nas ocorrencias de cada numero na ordem decrescente
void ordena_melhores_duplas(struct Melhores *melhores, int tamanho_melhores) {
	for(int i = 0; i < tamanho_melhores - 1; i++){ 
		for(int j = i + 1; j < tamanho_melhores - 1; j++) {
			if(melhores[i].ocorrencias < melhores[j].ocorrencias){ 
				struct Melhores aux = melhores[j]; 
				melhores[j] = melhores[i]; 
				melhores[i] = aux; 
      		}
		}
  	}
}

void gera_duplas(int duplas[][TOTAL_NUM], int sorteio[]) {
	for(int i = 0; i < TAM_SORTEIO; i++) {
		for(int j = i + 1; j < TAM_SORTEIO; j++) {
			if(j > i && sorteio[j] != sorteio[i])
				duplas[sorteio[i]-1][sorteio[j]-1]++;
		}
	}
}

int aumenta_melhores(struct Melhores **melhores, int tamanho_atual, int novos_elementos)
{
    int tamanho_total = tamanho_atual + novos_elementos;
    struct Melhores *temp = (struct Melhores*) realloc(*melhores, (tamanho_total * sizeof(struct Melhores)));

    if (temp == NULL)
    {
        printf("Memoria insuficiente.\n");
        exit(-2);
    }
    else
    {
        *melhores = temp;
    }

    if(melhores == NULL){
    	printf("melhores esta null\n");
    	exit(-2);
    }

    //printf("tamanho_melhores = %d\n", );


    return tamanho_total;
}

void gera_melhores_duplas(int duplas[][TOTAL_NUM], struct Melhores **melhores, int *tamanho_melhores) {

	for(int i = 0; i < TOTAL_NUM; i++) {
		for(int j = 0; j < TOTAL_NUM; j++) {
			if(duplas[i][j] > 0) {
				*tamanho_melhores = aumenta_melhores(melhores, *tamanho_melhores, 1);
				(*melhores)[(*tamanho_melhores)-1].numero1 = i + 1;
				(*melhores)[(*tamanho_melhores)-1].numero2 = j + 1;
				(*melhores)[(*tamanho_melhores)-1].ocorrencias = duplas[i][j];
			}
		}
	}
}

void gera_sorteio(int inicio, int final, int sorteio[], struct Lista_numeros lista_numeros[]){
	
	int numero = gera_numero(inicio, final);
	sorteio[0] = numero;

	// Gerar 6 numeros sempre diferentes
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
	int duplas[TOTAL_NUM][TOTAL_NUM];
	struct Melhores *melhores = NULL;
	int tamanho_melhores = 0;

	// Zerando valores da estrutura Lista_numeros
	for (int i = 0; i < TOTAL_NUM; i++){
		lista_numeros[i].numero = i + 1;
		lista_numeros[i].ocorrencias = 0;
		lista_numeros[i].ultimo_sorteio = 0;
	}

	// Zerando valores de cada numero do sorteio
	for(int i = 0; i < TOTAL_SORTEIO; i++){
		for (int j = 0; j < TAM_SORTEIO; j++){
			sorteios[i][j] = 0;
		}
	}

	// Zerando valores de cada matriz de duplas
	for(int i = 0; i < TOTAL_NUM; i++){
		for (int j = 0; j < TOTAL_NUM; j++){
			duplas[i][j] = 0;
		}
	}

	// Gerando 3000 numeros aleatorios entre 1 e 60 e salvando suas ocorrencias
	for (int i = 0; i < TOTAL_SORTEIO; i++){
		gera_sorteio(inicio, final, sorteios[i], lista_numeros);
		ordena_sorteio(sorteios[i]);
		printf("Sorteio[%d] = ", i+1); imprime_sorteio(sorteios[i]);
		gera_duplas(duplas, sorteios[i]);
	}

	// Ordena a ocorrencia de cada numero em ordem decrescente
	ordena_lista_numeros(lista_numeros);

	// Imprime os 15 numeros que mais ocorreram em ordem crescente
	imprime_lista_numeros(lista_numeros, 15);

	// Salva em arquivo os dados
	//salva_arquivo(f, ...);;
	fprintf(arquivo,"NUMERO;OCORRENCIAS\n");
	for (int i = 0; i < TOTAL_NUM; i++){
		//printf("o numero %d foi sorteado %d vezes\n", lista_numeros[i].numero, lista_numeros[i].ocorrencias);
		fprintf(arquivo,"%d;%d\n", lista_numeros[i].numero, lista_numeros[i].ocorrencias);
	}

	gera_melhores_duplas(duplas, &melhores, &tamanho_melhores);
	ordena_melhores_duplas(melhores, tamanho_melhores);
	imprime_melhores_duplas(melhores, 15);

	if (melhores != NULL)
		free(melhores);

	fclose(arquivo);
	return 0;
}