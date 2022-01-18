/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

char const VAZIO = '.';

void empurrarParaBaixo(char *matriz, int a, int l, int i, int j) {
    if (i < a - 1) {
        empurrarParaBaixo(matriz, a, l, i + 1, j);
        if (matriz[(i + 1) * l + j] == VAZIO) {
            printf("Empurrando %c em %d, %d...\n", matriz[i * l + j], i, j);
            matriz[(i + 1) * l + j] = matriz[i * l + j];
            matriz[i * l + j] = VAZIO;
        }
    }
}

void empurrarParaDireita(char *matriz, int a, int l, int i, int j) {
    if (j < l - 1) {
        empurrarParaDireita(matriz, a, l, i, j + 1);
        if (matriz[i * l + (j + 1)] == VAZIO) {
            printf("Empurrando %c em %d, %d...\n", matriz[i * l + j], i, j);
            matriz[i * l + (j + 1)] = matriz[i * l + j];
            matriz[i * l + j] = VAZIO;
        }
    }
}

void empurrarParaCima(char *matriz, int a, int l, int i, int j) {
    if (i > 0) {
        empurrarParaCima(matriz, a, l, i - 1, j);
        if (matriz[(i - 1) * l + j] == VAZIO) {
            printf("Empurrando %c em %d, %d...\n", matriz[i * l + j], i, j);
            matriz[(i - 1) * l + j] = matriz[i * l + j];
            matriz[i * l + j] = VAZIO;
        }
    }
}

void empurrarParaEsquerda(char *matriz, int a, int l, int i, int j) {
    if (j > 0) {
        empurrarParaEsquerda(matriz, a, l, i, j - 1);
        if (matriz[i * l + (j - 1)] == VAZIO) {
            printf("Empurrando %c em %d, %d...\n", matriz[i * l + j], i, j);
            matriz[i * l + (j - 1)] = matriz[i * l + j];
            matriz[i * l + j] = VAZIO;
        }
    }
}

void popularSlidePuzzle(char *vetor, int a, int l, char caractere, int indice) {
    if (indice + 1 < l * a) {
        vetor[indice] = caractere;
        popularSlidePuzzle(vetor, a, l, caractere + 1, indice + 1);
    } else {
        vetor[indice] = VAZIO;
    }
}

void imprimirMatriz(char *matriz, int a, int l) {
    int i,j;
    for (i = 0; i < a; i++) {
        for (j = 0; j < l; j++) {
            printf(" %c", matriz[i * l + j]);
        }
        printf("\n");
    }
}

int verificarOrdem(char *vetor, int a, int l, char caractere, int indice) {
    if (indice + 1 < l * a - 1) {
        if (vetor[indice + 1] != caractere + 1 && vetor[indice + 1] != VAZIO)
            return 0;
        return verificarOrdem(vetor, a, l, caractere + 1, indice + 1);
    } else {
        if (vetor[indice + 1] != caractere + 1 && vetor[indice + 1] != VAZIO)
            return 0;
        else return 1;
    }
}

void embaralhar(char *vetor, int tam, int indice) {
    int aux;
    int choice = rand() % indice;
    
    aux = vetor[indice];
    vetor[indice] = vetor[choice];
    vetor[choice] = aux;
    
    if (indice > 1)
        embaralhar(vetor, tam, indice - 1);
}

int converterNumToInt(char numero) {
    return numero - 48;
}

void pedirEscolhaPosicaoEmp(char *matriz, int a, int l, char *linhacoluna) {
    system("clear");
    imprimirMatriz(matriz, a, l);
    printf(" Informe linha e coluna nessa ordem e sem espaco: ");
    scanf("%s", linhacoluna);
}

int procurarElementoVer(char *matriz, int i, int a, int l, char elemento, int ignore) {
    int j;
    for (j = 0; j < a; j++) {
        if ((matriz[j * a + i] == elemento) && (j != ignore)) {
            return j;
        }
    }
    return -1;
}

int procurarElementoHor(char *matriz, int i, int a, int l, char elemento, int ignore) {
    int j;
    for (j = 0; j < l; j++) {
        if ((matriz[i * l + j] == elemento) && (j != ignore)) {
            return j;
        }
    }
    return -1;
}

void rodarJogo(char *matriz, int a, int l) {
    do {
        int i, j;
        char linhacoluna[2];
        pedirEscolhaPosicaoEmp(matriz, a, l, linhacoluna);
        i = converterNumToInt(linhacoluna[0]) - 1;
        j = converterNumToInt(linhacoluna[1]) - 1;
        if (procurarElementoHor(matriz, i, a, l, VAZIO, -1) >= 0) {
            empurrarParaDireita(matriz, a, l, i, j);
            empurrarParaEsquerda(matriz, a, l, i, j);
        } else if (procurarElementoVer(matriz, j, a, l, VAZIO, -1) >= 0) {
            empurrarParaBaixo(matriz, a, l, i, j);
            empurrarParaCima(matriz, a, l, i, j);
        }
    } while(!verificarOrdem(matriz, a, l, 'a', 0));
    printf(" Parabens! Vc ganhou!\n");
}

void testeVerificarOrdem(char *matriz, int a, int l) {
    popularSlidePuzzle(matriz, a, l, 'a', 0);
    imprimirMatriz(matriz, a, l);
    printf("Ta em ordem: %d\n", verificarOrdem(matriz, a, l, 'a', 0));
    embaralhar(matriz, a * l, a * l - 2);
    imprimirMatriz(matriz, a, l);
    printf("Ta em ordem: %d\n", verificarOrdem(matriz, a, l, 'a', 0));
}

void testeEmbaralhar(char *matriz, int a, int l) {
    printf("\nPopulando...\n");
    popularSlidePuzzle(matriz, a, l, 'a', 0);
    imprimirMatriz(matriz, a, l);
    printf("\nEmbaralhando...\n");
    embaralhar(matriz, a * l, a * l - 1);
    imprimirMatriz(matriz, a, l);
}

void testeEmpurrar(char *matriz, int a, int l) {
    printf("\nPopulando...\n");
    popularSlidePuzzle(matriz, a, l, 'a', 0);
    imprimirMatriz(matriz, a, l);
    int i, j;
    i = 0;
    j = 3;
    printf("\nEmpurrando em %d, %d\n", i, j);
    empurrarParaBaixo(matriz, a, l, i, j);
    imprimirMatriz(matriz, a, l);
    i = 0;
    j = 0;
    printf("\nEmpurrando em %d, %d\n", i, j);
    empurrarParaDireita(matriz, a, l, i, j);
    imprimirMatriz(matriz, a, l);
    i = 3;
    j = 0;
    printf("\nEmpurrando em %d, %d\n", i, j);
    empurrarParaCima(matriz, a, l, i, j);
    imprimirMatriz(matriz, a, l);
    i = 3;
    j = 3;
    printf("\nEmpurrando em %d, %d\n", i, j);
    empurrarParaEsquerda(matriz, a, l, i, j);
    imprimirMatriz(matriz, a, l);
}

void testeGameLoop(char *matriz, int a, int l) {
    popularSlidePuzzle(matriz, a, l, 'a', 0);
    embaralhar(matriz, a * l, a * l - 1);
    rodarJogo(matriz, a, l);
}

int main()
{
    printf("Hello World\n");
    
    char m[16];
    
    //imprimirMatriz(m, 4, 4);
    
    //testeVerificarOrdem(m, 4, 4);
    
    //testeEmpurrar(m, 4, 4);
    
    testeGameLoop(m, 4, 4);
    
    return 0;
}
