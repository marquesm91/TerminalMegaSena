# Terminal Mega Sena

Gerar dados estatísticos para o jogo Mega Sena.

## O que deve ser feito

Criar um programa na linguagem C sobre a MEGASENA com as seguintes funções:

* ~~Gerar numeros aleatorios entre 1 e 60.~~
* ~~Gerar 3000 sorteios realmente aleatórios, em uma matriz, cada um com 6 números únicos (01 a 60).~~
* ~~Exibir os números por ordem do sorteio.~~
* ~~Exibir os números de cada sorteio em ordem crescente.~~
* ~~Gerar uma lista de estatística com os seguintes dados: a) Quantidade de vezes que cada número saiu nos sorteios (Ordem crescente). Por exemplo: Numero 05 = 290 vezes.~~
* ~~Listar as 15 duplas que mais saíram nos sorteios. Por exemplo: Números 03 e 29 = 156 vezes.~~
* ~~Listar os 15 números únicos que mais saíram nos sorteios (Ordem crescente). Por exemplo: Numero 02 = 360 vezes.~~
* Listar de 01 a 60 a quantidade de jogadas desde a ultima vez que o número foi sorteado. Por exemplo: Nº 01 = não sai a 7 sorteios seguidos. Nº 02 = não sai a 15 sorteios seguidos. Nº 03 = saiu no ultimo sorteio. Nº 04 = não sai a 31 sorteios seguidos Nº 05 = não sai a 3 sorteios seguidos .... Até o Nº 60.
* Simular uma jogada para 3 usuários diferentes, com os seguintes dados: a) Capturar o nome do apostador. b) Capturar 6 números para o sorteio (validar os números escolhidos, de 01 a 60).
* Após as jogadas dos 3 usuários, indicar qual o máximo de números cada usuário acertou, com base nos 3000 sorteios anteriores, e indicar qual o seu melhor resultado, ou seja, em qual sorteio o jogador acertou mais números (informar também a quantidade). Exemplo: Parabéns `<nome do apostador>`, no sorteio `<número do sorteio>` você acertou `<quantidade de números>` números!