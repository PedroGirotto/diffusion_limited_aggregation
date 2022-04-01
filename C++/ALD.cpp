#include<iostream>
#include<cstdlib>

using namespace std;

class Gota
{
    private:
        int comprimento, altura;
        int *regiao;

    public:
        Gota(int* inRegiao, int inComprimento, int inAltura);
};

int* GerarRegiao(int comprimento, int altura);

int main()
{
    int comprimento, altura;
    comprimento = 100;
    altura = 100;

    int* regiao = GerarRegiao(comprimento, altura);

    Gota gota(regiao, comprimento, altura);

    for(int i = 0; i < altura; i++)
    {
        for(int j = 0; j < comprimento; j++)
        {
            cout << regiao[i*altura + j];
        }
        cout << endl;
    }

    free(regiao);
    return 0;
}


int* GerarRegiao(int comprimento, int altura)
{
    int* regiao = (int *) calloc(comprimento*altura, sizeof(int));
    int passo = (int) (comprimento/(comprimento*0.1));

    for(int i = 0; i < (int) (comprimento*0.1 + 1); i++)
    {
        if(i*passo >= comprimento)
        {
            regiao[comprimento*altura - 1] = 1;
        }
        else
        {
            regiao[(altura*(altura-1)) + i*passo] = 1;
        }
    }

    return regiao;
}


Gota::Gota(int* inRegiao, int inComprimento, int inAltura)
{
    regiao = inRegiao;
    comprimento = inComprimento;
    altura = inAltura;
}