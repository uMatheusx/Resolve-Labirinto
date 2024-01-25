/*********************************************************************/
/**   ACH2002 - Introducao a Analise de Algoritmos                  **/
/**   EACH-USP - Segundo Semestre de 2023                           **/
/**   Turma 04 - Prof. Luciano Digiampietri                         **/
/**                                                                 **/
/**   Primeiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   <Matheus Ferreira Azevedo>                <14760276>          **/
/**                                                                 **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

int varX[] = {1,0,0,-1};
int varY[] = {0,-1,1,0};

typedef int bool;


/* Estrutura que define um labirinto 
   linhas: numero de linhas (altura)
   colunas: numero de colunas (largura)
   inicioX: posicao inicial no eixo X
   inicioY: posicao inicial no eixo Y
   fimX: posicao final (destino/saida) no eixo X
   fimY: posicao final (destino/saida) no eixo Y
   labirinto: labirinto propriamente dito, representado como uma matriz
              (um arranjo de arranjos) de caracteres
*/
typedef struct {
    int linhas;
    int colunas;
    int inicioX;
    int fimX;
    int inicioY;
    int fimY;
    char** labirinto;
} LABIRINTO;

bool resolveLabirintoAux(LABIRINTO lab, int x, int y);


/* Funcao auxiliar para o sistema de correcao (nao mexer) */
void printf123(){
    // Funcao usada pelo sistema de correcao (nao mexer)
}


/* Funcao para criar um labirinto inicial (sem paredes internas), com as 
   dimensoes passadas como entrada, bem como as posicoes inicial e final. */
LABIRINTO criarLabirintoBase(int lin, int col, int iniX, int iniY, int fimX, int fimY){
    int x, y;
    printf("##### Criando labirindo de tamanho %i x %i, com inicio na posicao (%i,%i) e fim na posicao (%i,%i). #####\n", lin, col, iniX, iniY, fimX, fimY);
    LABIRINTO lab;
    lab.linhas = lin;
    lab.colunas = col;
    lab.inicioX = iniX;
    lab.fimX = fimX;
    lab.inicioY = iniY;
    lab.fimY = fimY;
    lab.labirinto = (char**) malloc(sizeof(char*)*lin);
    for (x=0;x<lin;x++)
        lab.labirinto[x] = (char*) malloc(sizeof(char)*col);  
    for (x=0;x<lin;x++)
        for (y=0;y<col;y++)
            lab.labirinto[x][y] = ' ';
            
    for (x=0;x<lin;x++){
        lab.labirinto[x][0] = '#';
        lab.labirinto[x][col-1] = '#';
    }
    
    for (y=0;y<col;y++){
        lab.labirinto[0][y] = '#';
        lab.labirinto[lin-1][y] = '#';
    }
    lab.labirinto[lab.inicioX][lab.inicioY] = 'I';
    lab.labirinto[lab.fimX][lab.fimY] = 'F';
    return lab;
}


/* Funcao para gerar ate uma certa quantidade de paredes de forma
   pseudoaleatoria dentro do labirinto passado como parametro.     */
void gerarParedes(LABIRINTO lab, int paredes){
    int px;
    int py;
    int p;
    for (p=0;p<paredes;p++){
        px = 1+rand() % (lab.linhas-1);
        py = 1+rand() % (lab.colunas-1);
        lab.labirinto[px][py] = '#';
    }
    lab.labirinto[lab.inicioX][lab.inicioY] = 'I';
    lab.labirinto[lab.fimX][lab.fimY] = 'F';
}


/* Funcao que imprime o labirinto passado como parametro */
void imprimirLabirinto(LABIRINTO lab){
    int x, y;
    printf("Imprimindo o labirinto\n");
    for (x=0;x<lab.linhas;x++){
        for (y=0;y<lab.colunas;y++)
            printf("%c",lab.labirinto[x][y]);
        printf("\n");
    }
    printf("\n");
}


bool resolveLabirinto(LABIRINTO lab){
    return resolveLabirintoAux(lab, lab.inicioX, lab.inicioY); 
}

bool resolveLabirintoAux(LABIRINTO lab, int atualx, int atualy) {
    // Verificação de parada, ou seja se chegar na coordenada final do labirinto.
    if (atualx == lab.fimX && atualy == lab.fimY) {
        return true;
    }

    // Verificação se pode haver passos, ou seja, se é um espaço vazio ou o início!
    if (lab.labirinto[atualx][atualy] == ' ' || lab.labirinto[atualx][atualy] == 'I') {
        // Colocar um ponto para marcar o caminho, se não houver nada impedindo.
        if (lab.labirinto[atualx][atualy] == ' ') lab.labirinto[atualx][atualy] = '.';

        // for que irá realizar a tentativa de cada um dos lados: baixo, esquerda, direita e cima, respectivamente.
        // tudo isso com base na varX e varY que dependendo do valor irá pegar o valor de i e puxar de um array que
        // é responsável por fazer essa movimentação.
        for (int i = 0; i < 4; i++) {
            int newX = atualx + varX[i];
            int newY = atualy + varY[i];

            if (lab.labirinto[newX][newY] == 'I')  // verificação para impedir que o valor inicial seja alterado.
            {
                continue;
            }

            // Faz a chamada recursiva 
            if (resolveLabirintoAux(lab, newX, newY)) {
                return true;  
            }
        }

        
        if (lab.labirinto[atualx][atualy] == '.') lab.labirinto[atualx][atualy] = ' '; // Faz o backtracking voltando uma casa
    }

    return false;
}

int main() {
    // Inicializando gerador de numeros pseudo aleatorios
    srand(42);
    LABIRINTO lab1;

    lab1 = criarLabirintoBase(4,4,1,1,2,2);
    printf("Labirinto vazio\n");
    imprimirLabirinto(lab1);
    printf("Gerando paredes aleatoriamente\n");
    gerarParedes(lab1, 1);
    imprimirLabirinto(lab1);
    if (resolveLabirinto(lab1)) printf("Saida encontrada!\n");
    else printf("Saida nao encontrada!\n");
    imprimirLabirinto(lab1);


    lab1 = criarLabirintoBase(5,5,1,1,3,3);
    printf("Labirinto vazio\n");
    imprimirLabirinto(lab1);
    if (resolveLabirinto(lab1)) printf("Saida encontrada!\n");
    else printf("Saida nao encontrada!\n");
    imprimirLabirinto(lab1);



    lab1 = criarLabirintoBase(5,5,3,3,1,1);
    printf("Labirinto vazio\n");
    imprimirLabirinto(lab1);
    if (resolveLabirinto(lab1)) printf("Saida encontrada!\n");
    else printf("Saida nao encontrada!\n");
    imprimirLabirinto(lab1);


    lab1 = criarLabirintoBase(10,20,8,1,8,18);
    printf("Labirinto vazio\n");
    imprimirLabirinto(lab1);
    printf("Gerando paredes aleatoriamente\n");
    gerarParedes(lab1, 60);
    imprimirLabirinto(lab1);
    if (resolveLabirinto(lab1)) printf("Saida encontrada!\n");
    else printf("Saida nao encontrada!\n");
    imprimirLabirinto(lab1);
    
    
    lab1 = criarLabirintoBase(4,4,1,1,2,2);
    printf("Labirinto vazio\n");
    imprimirLabirinto(lab1);
    lab1.labirinto[1][2] = '#';
    lab1.labirinto[2][1] = '#';
    imprimirLabirinto(lab1);
    if (resolveLabirinto(lab1)) printf("Saida encontrada!\n");
    else printf("Saida nao encontrada!\n");
    imprimirLabirinto(lab1);
    
    
    return 0;
}

