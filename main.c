#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
char AlfaA = {A,B,C,D,E,F,G,H,I,J};
char AlfaB = {a,b,c,d,e,f,g,h,i,j};*/


void menu() {

}

void geraTabIni(int tab[10][10]){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            tab[i][j] = '-';
        }
    }
}

void geraCampo(int mat[10][10]) {
    srand(time(NULL));
    int min = -1;
    int max = 4;

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            mat[i][j] = (rand() % (max - min + 1)) + min;
        }
    }
}

void imprime(int mat[10][10]){
    printf("\n");
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            printf(" %c ", mat[i][j]);
        }

        printf("\n");
    }

}

int main() {
    printf("Campo Minado iniciado\n");
    int mat[10][10];

    geraCampo(mat);
    int tabInic[10][10];
    geraTabIni(tabInic);
    imprime(tabInic);


}
//
// Created by luiza on 16/09/2024.
//
