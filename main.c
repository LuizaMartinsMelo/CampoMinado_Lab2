#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//---------Define--------//
#define LINHAS 10
#define COLUNAS 10

/*
char AlfaA = {A,B,C,D,E,F,G,H,I,J};
char AlfaB = {a,b,c,d,e,f,g,h,i,j};*/

//--------Variáveis Global--------//
int count_dicas = 0; //contador global das função dica
int inicio = 0;

//---------Protótipos das funções--------//
void menu();
void opcao();
void ajuda();
void dica();
void configuracao();
void iniciar();
void pausar();
void continuar();
void jogada();
void sair();
void geraTabIni(int tab[10][10]);
void geraCampo(int mat[10][10]);
void imprime(int mat[10][10]);
void relogio();

//---------Função Principal--------//
int main() {
    int tabuleiro[LINHAS][COLUNAS] = {0};
    printf("***Jogo Iniciado***\n\n")
/*
    geraCampo(mat);
    geraTabIni(tabInic);
    imprime(tabInic);
*/
    while(1) {
        menu();
        opcao();
    }

    return 0;

}

//---------Funções---------//
void menu() {
    printf(
        "\n//---MENU---//\n"
        "OPCOES:\n"
        "Clique em alguma letra indicada na frente das opcoes.\n"
        "A - AJUDA\n"
        "D - DICA\n"
        "C - CONFIGURACAO\n"
        "I - INICIAR\n"
        "P - PAUSAR\n"
        "T - CONTINUAR\n"
        "J - JOGADA\n"
        "S - SAIR\n"
        "Escolha uma opcao: \n"
    );
}
void opcao() {
    char op;
    op = getchar();
    switch (op) {
        case 'A':
        case 'a':
            puts("deu");
            ajuda();
            break;
        case 'D':
        case 'd':
            dica();
        break;
        case 'C':
        case 'c':
            configuracao();
        break;
        case 'I':
        case 'i':
            iniciar();
        break;
        case 'P':
        case 'p':
            pausar();
        break;
        case 'T':
        case 't':
            continuar();
        break;
        case 'J':
        case 'j':
            jogada();
        break;
        case 'S':
        case 's':
            sair();
        break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
    }
    fflush(stdin);
}

void ajuda() {
    printf(
        "\n   Regras do jogo:   \n"
            "O objetivo do jogo e revelar todas as celuas que nao contem bomba.\n"
            "Se voce revelar uma celula com uma bomba, o jogo termina.\n"
            "Os numero nas celulas indicam quantas bombas estao nas proximidades.\n"
    );
}

//funcao que da uma dica para o jogador
void dica() {
    count_dicas++;
    switch (count_dicas) {
        case 1:
            printf("Dica: comece pelas bordas, pode ser mais seguro\n\n.");
            break;
        case 2:
            printf("Dica: Use os numeros, eles mostram quantas minas tem ao redor.\n\n");
            break;
        case 3:
            printf("Dica: Cuidado com os numeros altos, como (5) indica muitas minas por perto.\n\n");
            break;
        case 4:
            printf("Dica: Encontrou um (1)? Se você já marcou uma mina ao lado, as outras casas ao redor são seguras para abrir. Isso pode limpar uma grande área de uma vez.\n\n");
            break;
        case 5:
            printf("Dica: ");
            break;
        case 6:
            printf("Dica 6");
            break;
        case 7:
            printf("Dica 7");
            break;
        case 8:
            printf("Dica 8");
            break;
            count_dicas = 0;
    }
}

void configuracao() {
    int nivel;
    printf("Selecione o nivel de dificuldade(1, 2 ou 3)");
    scanf("%d", &nivel);
    printf("Nivel %d selecionado", nivel);
}

void iniciar() {
    if(inicio == 0) {
        printf("Campo Minado iniciado\n");


        printf("Tabuleiro montado e relogio iniciado!");
    }else {
        printf("\nJogo já foi iniciado!",
                    "\nDeseja reiniciar o jogo?(S/N)");

    }

}

void pausar() {
    printf("Jogo pausado");
}

void continuar() {
    printf("Retomando o jogo");
}

void jogada() {
    int linha, coluna;
    printf("Informe a linha e a coluna para revelar uma celula: ");
    scanf("%d %d", &linha, &coluna);
    printf("Celula (%d, %d) revelada.\n", linha, coluna);
}

void sair () {
    printf("Jogo finalizado!");
    exit(0);
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

void relogio() {
    time_t tempo_inicio, tempo_atual,tempo_pausa;
    int segundos_decorridos = 0, pausado = 0;
    char opcao;

    tempo_atual = time(NULL);

    while(1) {
        if(!pausado) {
            tempo_atual = time(NULL);
            segundos_decorridos = (int) tempo_atual - tempo_inicio;//calcula o tempo decorrido
            printf("\nTempo decorrido: %d segundos", segundos_decorridos);
            fflush(stdout);
        }
        sleep(1);//Pausa o tempo por 1 segundo

        if(pausado) {
            printf("\nRelogio pausado. Escolha uma opcao(C: Para continuar ou S: Para sair): ");
        }else {
            printf("\nEscolha (P: Pausar ou S: Sair): ");
        }
        scanf("%c", &opcao);

        if(opcao == 'P'||opcao == 'p') {
            if(!pausado){
                tempo_pausa = time(NULL);
                pausado=1;
                printf("\nRelogio pausado.");
            }
        }
    }
}