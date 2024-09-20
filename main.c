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
void menu(); //ok
void opcao(int *bombas);
void ajuda();
void dica();
void configuracao(int *bombas); //ok
void iniciar(int *bombas);
void pausar();
void continuar();
void jogada();
void sair();
void geraTabIni(int tab[10][10]);
void geraCampo(int mat[10][10], int *bombas);
void imprime(int mat[10][10]); //auxiliar
void relogio();

//---------Função Principal--------//
int main() {
    int campo[LINHAS][COLUNAS] = {0};
    int mat[LINHAS][COLUNAS] = {0};
    int bomba;
    printf("Jogo Iniciado\n\n");
/*
  imprime(tabInic);
*/
    geraTabIni(campo);
    while(1) {
        imprime(campo);
        menu();
        opcao(&bomba);
        printf("\nBomba: %d\n", bomba);
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

void opcao(int *bomba) {
    char op;
    op = getchar();
    switch (op) {
        case 'A':
        case 'a':
            ajuda();
            break;
        case 'D':
        case 'd':
            dica();
        break;
        case 'C':
        case 'c':
            configuracao(bomba);
        break;
        case 'I':
        case 'i':
            iniciar(bomba);
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
            count_dicas = 0;
            break;
    }
}

void configuracao(int *bombas) {
    int nivel;
    int foi = 1;
    while(foi) {
        printf("\nSelecione o nivel de dificuldade(1, 2 ou 3): ");
        scanf("%d", &nivel);
        switch (nivel) {
            case 1:
                *bombas = 10;
                foi = 0;
            break;
            case 2:
                *bombas = 15;
                foi = 0;
            break;
            case 3:
                *bombas = 20;
                foi = 0;
            break;
            default:
                printf("Nivel inexistente\n");
        }
    }
    printf("\nNivel %d selecionado", nivel);
}

void iniciar(int *bombas) {
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

void geraCampo(int campo[10][10], int *bombas) {
    int bombasColocadas = 0;

    while (bombasColocadas < *bombas) {
        int linha = rand() % LINHAS;
        int coluna = rand() % COLUNAS;

        if (campo[linha][coluna] != -1) {  // Verifica se não já é uma bomba
            campo[linha][coluna] = -1;  // Coloca uma bomba
            bombasColocadas++;
        }
    }
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (campo[i][j] == -1) {  // Se for uma bomba
                // Incrementa o valor nas células adjacentes
                for (int x = -1; x <= 1; x++) {
                    for (int y = -1; y <= 1; y++) {
                        int novaLinha = i + x;
                        int novaColuna = j + y;

                        // Verifica se está dentro dos limites e se não é uma bomba
                        if (novaLinha >= 0 && novaLinha < LINHAS &&
                            novaColuna >= 0 && novaColuna < COLUNAS &&
                            campo[novaLinha][novaColuna] != -1) {
                            campo[novaLinha][novaColuna]++;
                            }
                    }
                }
            }
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