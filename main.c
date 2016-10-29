#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int geraNumero(int inicio, int final) {
  int random_number = rand(); // entre 1 and RAND_MAX (constante stdlib.h)

  // Alterando o range para [0,final) de random_number
  random_number = random_number % final;  // [0,60)

  // Alterando o range para [inicio, inicio + final) ou [inicio, inicio + final - 1] de random_number 
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

  // Gerando 3000 numeros aleatorios
  for (int i = 0; i < 3000; i++){
    int index = geraNumero(inicio, final);
    listaNumeros[index]++;
  }

  fprintf(f,"NUMERO;OCORRENCIAS\n");
  // Imprimindo resultados
  for (int i = 0; i < 60; i++){
    printf("o numero %d foi sorteado %d vezes\n", i+1, listaNumeros[i]);
    fprintf(f,"%d;%d\n", i+1, listaNumeros[i]);
  }
  
  fclose(f);
  return 0;
}