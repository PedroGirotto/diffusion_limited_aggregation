#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;


// variáveis globais para armazenar o tamanho da linha e da coluna da matriz
int lin, col;


// definições das funções
void gerarMatriz(int* matriz);
void imprimirMatriz(int* matriz, ofstream &MyFile);
void gerarSemente(int* matriz, int linha, int coluna);
void gerarGota(int* matriz, int &linha, int &coluna);
void moverGota(int* matriz, int &linha, int &coluna, bool &parada);


// ------------------------------------------------
// Significado dos valores numéricos:
// 0 - representa espaço vazio
// 1 - representa uma semente
// 2 - representa uma semente germinada
// 3 - representa uma gota da água


// ------------------------------------------------
// A ideia do algoritmo é criar uma matriz de dimensão linXcol
// onde inicializamos essa matriz e criamos uma gota (ambos possuem suas funções)
// depois disso entraremos em um laço de repetição até a condição de parada ser alcançada (semente germinada na primeira linha)
// o laço de repetição funciona da seguinte maneira, mover uma gota até ela germinar uma semente
// quando a gota germina uma semente suas cordenadas teram os valores -1
// o que sinalizar para gerar uma nova semente e assim o processo se repete.

int main()
{
    srand(time(NULL));

    // coordenadas da gota
    int linha, coluna;

    // valor da condição de parada, começa como 'false' por que no estado inicial essa condição ainda não foi alcançada
    bool parada = false;

    // arquivo de texto contendo a matriz final
    ofstream MyFile("matriz.txt");

    // recebendo os valores para criar a matriz
    cout << "Digite a quantidade de linhas da matriz: ";
    cin >> lin;
    cout << "Digite a quantidade de colunas da matriz: ";
    cin >> col;

    // criando a matriz com os valores passado pelo usuário
    int* matriz = new int[lin*col];

    // gerar a matriz
    gerarMatriz(matriz);

    // gerar a gota
    gerarGota(matriz, linha, coluna);

    // laço principal do processo
    // o laço acontecerá até a condição de parada ser alcançada
    while(!parada)
    {
        // se a gota existir, mover-la
        if(linha != -1 && coluna != -1)
        {
            moverGota(matriz, linha, coluna, parada);
        }

        // se a gota não existir (germinou uma semente), gerar uma nova gota
        else
        {
            gerarGota(matriz, linha, coluna);
        }
    }

    // imprimir a matriz final
    imprimirMatriz(matriz, MyFile);

    // fechar o arquivo de texto
    MyFile.close();
    system("PAUSE");
    return 0;
}


// ------------------------------------------------
// função que gerar a matriz em seu espado inicial
// todos os valores serão iguais a zero meno da ultima linha que serão iguais a 1
void gerarMatriz(int* matriz)
{
    for(int i = 0; i < lin-1; i++)
    {
        for(int j = 0; j < col; j++)
        {
            matriz[i*col + j] = 0;
            
        }
    }
    for(int j = 0; j < col; j++)
    {
        matriz[(lin-1)*col + j] = 1;
            
    }
}


// função para imprimir os valores da matriz em um arquivo de texto
// na qual será processada por um script em python para fazer o plot
void imprimirMatriz(int* matriz, ofstream &MyFile)
{
    for(int i = 0; i < lin; i++)
    {
        for(int j = 0; j < col; j++)
        {
            MyFile << matriz[i*col + j] << "\t";
        }
        MyFile << endl;
    }
}


// função que gera novas sementes quando é germinada
// essa função tem como parâmetro a matriz e as coordenadas da semente germinada (linha e coluna)
void gerarSemente(int* matriz, int linha, int coluna)
{
    // verifica se não está na borda superior ou inferior
    if(linha > 0 && linha < lin-1)
    {
        // caso a semente esteja na primeira coluna
        // criar novas sementes acima, abaixo e para direita
        if(coluna == 0)
        {
            // semente abaixo
            if(matriz[(linha+1)*col + coluna] == 0)
                matriz[(linha+1)*col + coluna] = 1;
            // semente acima
            if(matriz[(linha-1)*col + coluna] == 0)
                matriz[(linha-1)*col + coluna] = 1;
            // semente a direita
            if(matriz[(linha)*col + (coluna+1)] == 0)
                matriz[(linha)*col + (coluna+1)] = 1;
        }

        // caso a semente esteja na ultima coluna
        // criar novas sementes acima, abaixo e para esquerda
        else if(coluna == col-1)
        {
            // semente abaixo
            if(matriz[(linha+1)*col + coluna] == 0)
                matriz[(linha+1)*col + coluna] = 1;
            // semente acima
            if(matriz[(linha-1)*col + coluna] == 0)
                matriz[(linha-1)*col + coluna] = 1;
            // semente a esquerda
            if(matriz[(linha)*col + (coluna-1)] == 0)
                matriz[(linha)*col + (coluna-1)] = 1;
        }

        // caso a semente não esteja em nenhuma borda
        // criar novas sementes em todas as direções (acima, abaixo, direita e esqueda)
        else
        {
            // semente abaixo
            if(matriz[(linha+1)*col + coluna] == 0)
                matriz[(linha+1)*col + coluna] = 1;
            // semente acima
            if(matriz[(linha-1)*col + coluna] == 0)
                matriz[(linha-1)*col + coluna] = 1;
            // semente a esquerda
            if(matriz[(linha)*col + (coluna-1)] == 0)
                matriz[(linha)*col + (coluna-1)] = 1;
            // semente a direita
            if(matriz[(linha)*col + (coluna+1)] == 0)
                matriz[(linha)*col + (coluna+1)] = 1;
        }
    }

    // verifica se estar na borda superior
    else if(linha == 0)
    {
        // caso a semente esteja na ponta superior a esquerda
        // criar semente abaixo e para direita
        if(coluna == 0)
        {
            // semente a direita
            if(matriz[linha*col + (coluna+1)] == 0)
                matriz[linha*col + (coluna+1)] = 1;
            // semente abaixo
            if(matriz[(linha+1)*col + coluna] == 0)
                matriz[(linha+1)*col + coluna] = 1;
        }

        // caso a semente esteja na ponta superior a direita
        // criar semetne abaixo e para esquerda
        else if(coluna == col-1)
        {
            // semente a esquerda
            if(matriz[linha*col + (coluna-1)] == 0)
                matriz[linha*col + (coluna-1)] = 1;
            // semente abaixo
            if(matriz[(linha+1)*col + coluna] == 0)
                matriz[(linha+1)*col + coluna] = 1;
        }

        // caso a semente não esteja nas pontas
        // criar semente abaixo para esquerda e para direita
        else
        {
            if(matriz[linha*col + (coluna-1)] == 0)
                matriz[linha*col + (coluna-1)] = 1;
            if(matriz[linha*col + (coluna+1)] == 0)
                matriz[linha*col + (coluna+1)] = 1;
            if(matriz[(linha+1)*col + coluna] == 0)
                matriz[(linha+1)*col + coluna] = 1;
        }
    }

    // verificar se estar na borda inferior
    else
    {
        // como a ultima linha é feita por sementes
        // só há a necessidade de gerar uma semente para cima
        if(matriz[(linha-1)*col + coluna] == 0)
            matriz[(linha-1)*col + coluna] = 1;
    }
}


// função que gera a posição inicial da gota
// a gota é gerada na primeira linha onde o valor da coluna é gerada de forma aleatória
// os parâmetros são feitos por referência, então os valores são atualizadas para as variáveis passadas pelo parâmetro
void gerarGota(int* matriz, int &linha, int &coluna)
{
    // enquanto a gota não for gerada
    // a saida do laço é feita pelo 'break'
    while(true)
    {
        // valor da coluna gerada de forma aleatória.
        //valor entre 0 e a quantidade de colunas - 1
        int posicao = rand()%col;

        // se o valor na posição gerada for igual a zero, então podemos criar a gota
        if(matriz[posicao] == 0)
        {
            // gerando a gota
            matriz[posicao] = 3;

            //definindo a coordenada x
            linha = 0;

            // definindo a coordenada y
            coluna = posicao;
            break;
        }
    }
}


// função que faz o movimento da gota
// a função recepe como parâmetro a matriz, as coordenadas da gota (linha e coluna) e a condição de parada
// como os parâmetros estão sendo passadas por referência, então as coordenadas da gota são atualizadas ao decorrer da função
// se a condição de para for alcançada, a variável 'parada' se tornará 'true'
void moverGota(int* matriz, int &linha, int &coluna, bool &parada)
{
    // auxiliar para efetuar a troca de valores entre as posições da matriz
    int troca;

    // se o valor for par, a gota vai andar para baixo
    // se o valor for ímpar, a gota vai escolher um lado para andar e depois ir para baixo
    int direcao = (rand()%100)%2;

    // se a gota estiver na primeira coluna, ela vai andar para direita (já que não é possível ir para esquerda)
    if(coluna == 0 && direcao == 1)
    {
        // se o valor à direita for igual a zero, mover a gota de água
        if(matriz[linha*col + (coluna+1)] == 0)
        {
            // troca de possição dos valores da matriz
            troca = matriz[linha*col + coluna];
            matriz[linha*col + coluna] = matriz[linha*col + (coluna+1)];
            matriz[linha*col + (coluna+1)] = troca;

            // atualização da coordenada da gota
            coluna += 1;
        }

        // se o valor à direita for igual a uma semente, germinar a semente
        else if(matriz[linha*col + (coluna+1)] == 1)
        {
            // se estiver na primeira linha, a condição de parada foi alcançada
            if(linha == 0)
                parada = true;
            
            // colocando o valor da semente para germinada
            matriz[linha*col + (coluna+1)] = 2;

            // zerando o valor da gota da água
            matriz[linha*col + coluna] = 0;

            // chamando a função para gerar as novas sementes
            gerarSemente(matriz, linha, coluna+1);

            // como a gota da água não existe mais, transformar suas coordenadas para -1
            linha = -1;
            coluna = -1;
        }
    }

    // se a gota estiver na última coluna, ela vai andar para esquerda (já que não é possível ir para direita)
    else if(coluna == col-1 && direcao == 1)
    {
        // se o valor à esquerda for igual a zero, mover a gota de água
        if(matriz[linha*col + (coluna-1)] == 0)
        {
            // troca de possição dos valores da matriz
            troca = matriz[linha*col + coluna];
            matriz[linha*col + coluna] = matriz[linha*col + (coluna-1)];
            matriz[linha*col + (coluna-1)] = troca;

            // atualização da coordenada da gota
            coluna -= 1;
        }

        // se o valor à esquerda for igual a uma semente, germinar a semente
        else if(matriz[linha*col + (coluna-1)] == 1)
        {
            // se estiver na primeira linha, a condição de parada foi alcançada
            if(linha == 0)
                parada = true;

            // colocando o valor da semente para germinada
            matriz[linha*col + (coluna-1)] = 2;

            // zerando o valor da gota da água
            matriz[linha*col + coluna] = 0;

            // chamando a função para gerar as novas sementes
            gerarSemente(matriz, linha, coluna-1);

            // como a gota da água não existe mais, transformar suas coordenadas para -1
            linha = -1;
            coluna = -1;
        }
    }

    // a gota não está na borda à direita nem na esquerda
    else if(direcao == 1)
    {
        // se for par a gota se move para esquerda
        // se for ímpar a gota se move para direita
        int direcao = (rand()%100)%2;

        // movimentação para esquerda
        if(direcao == 0)
        {
            // se o valor à esquerda for igual a zero, mover a gota de água
            if(matriz[linha*col + (coluna-1)] == 0)
            {
                // troca de possição dos valores da matriz
                troca = matriz[linha*col + coluna];
                matriz[linha*col + coluna] = matriz[linha*col + (coluna-1)];
                matriz[linha*col + (coluna-1)] = troca;

                // atualização da coordenada da gota
                coluna -= 1;
            }

            // se o valor à esquerda for igual a uma semente, germinar a semente
            else if(matriz[linha*col + (coluna-1)] == 1)
            {
                // se estiver na primeira linha, a condição de parada foi alcançada
                if(linha == 0)
                    parada = true;
                
                // colocando o valor da semente para germinada
                matriz[linha*col + (coluna-1)] = 2;

                // zerando o valor da gota da água
                matriz[linha*col + coluna] = 0;

                // chamando a função para gerar as novas sementes
                gerarSemente(matriz, linha, coluna-1);

                // como a gota da água não existe mais, transformar suas coordenadas para -1
                linha = -1;
                coluna = -1;
            }
        }

        // movimentação para direita
        else if(direcao == 1)
        {
            // se o valor à direita for igual a zero, mover a gota de água
            if(matriz[linha*col + (coluna+1)] == 0)
            {
                // troca de possição dos valores da matriz
                troca = matriz[linha*col + coluna];
                matriz[linha*col + coluna] = matriz[linha*col + (coluna+1)];
                matriz[linha*col + (coluna+1)] = troca;

                // atualização da coordenada da gota
                coluna += 1;
            }

            // se o valor à direita for igual a uma semente, germinar a semente
            else if(matriz[linha*col + (coluna+1)] == 1)
            {
                // se estiver na primeira linha, a condição de parada foi alcançada
                if(linha == 0)
                    parada = true;

                // colocando o valor da semente para germinada
                matriz[linha*col + (coluna+1)] = 2;

                // zerando o valor da gota da água
                matriz[linha*col + coluna] = 0;

                // chamando a função para gerar as novas sementes
                gerarSemente(matriz, linha, coluna+1);

                // como a gota da água não existe mais, transformar suas coordenadas para -1
                linha = -1;
                coluna = -1;
            }
        }
    }

    // se nenhuma das sementes foram germinadas durante o processo de andar para os lados
    // então poderá fazer a movimentação para baixo
    if(linha != -1 && coluna != -1)
    {
        // se o valor abaixo for igual a zero, mover a gota de água
        if(matriz[(linha+1)*col + coluna] == 0)
        {
            // troca de possição dos valores da matriz
            troca = matriz[linha*col + coluna];
            matriz[linha*col + coluna] = matriz[(linha+1)*col + coluna];
            matriz[(linha+1)*col + coluna] = troca;

            // atualização da coordenada da gota
            linha += 1;
        }

        // se o valor abaixo for igual a uma semente, germinar a semente
        else if(matriz[(linha+1)*col + coluna] == 1)
        {
            // colocando o valor da semente para germinada
            matriz[(linha+1)*col + coluna] = 2;

            // zerando o valor da gota da água
            matriz[linha*col + coluna] = 0;

            // chamando a função para gerar as novas sementes
            gerarSemente(matriz, linha+1, coluna);

            // como a gota da água não existe mais, transformar suas coordenadas para -1
            linha = -1;
            coluna = -1;
        }
    }
}
