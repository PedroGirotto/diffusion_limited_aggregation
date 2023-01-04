#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include <vector>
#include <fstream>
using namespace std;

class Gota
{
    private:
        int x;
        int y;
        const int comprimento;
        const int altura;
        int *regiao;
    
        bool MoveDireita()
        {
            if(x == comprimento-1) // Na borda, logo o movimento faz sair da região
            {
                regiao[y*comprimento + x] = 0; // Zero representa que a gota foi destruida
            }
            else if(regiao[y*comprimento + (x+1)] == 0) // Nada no caminho, mover para direita
            {
                regiao[y*comprimento + (x+1)] = 2;
                regiao[y*comprimento + x] = 0;
                x += 1;
            }
            else if(regiao[y*comprimento + (x+1)] == 1) // Encontrou uma semente no caminho para direita, não mover e virar semente
            {
                regiao[y*comprimento + x] = 1;
                if(y == 0)
                {
                    return true; // Caso uma gota vire semente no spawn, retorne True
                }
            }

            return false; // Qualquer outro caso que não seja uma gota virando semente no spawn, retorne False
        }

        bool MoveEsquerda()
        {
            if(x == 0) // Na borda, logo o movimento faz sair da região
            {
                regiao[y*comprimento + x] = 0; // Zero representa que a gota foi destruida
            }
            else if(regiao[y*comprimento + (x-1)] == 0) // Nada no caminho, mover para esquerda
            {
                regiao[y*comprimento + (x-1)] = 2;
                regiao[y*comprimento + x] = 0;
                x -= 1;
            }
            else if(regiao[y*comprimento + (x-1)] == 1) // Encontrou uma semente no caminho para esquerda, não mover e virar semente
            {
                regiao[y*comprimento + x] = 1;
                if(y == 0)
                {
                    return true; // Caso uma gota vire semente no spawn, retorne True
                }
            }

            return false; // Qualquer outro caso que não seja uma gota virando semente no spawn, retorne False
        }

        bool MoveCima()
        {
            if(y == 0) // Na borda, logo o movimento faz sair da região
            {
                regiao[y*comprimento + x] = 0; // Zero representa que a gota foi destruida
            }
            else if(regiao[(y-1)*comprimento + x] == 0) // Nada no caminho, mover para cima
            {
                regiao[(y-1)*comprimento + x] = 2;
                regiao[y*comprimento + x] = 0;
                y -= 1;
            }
            else if(regiao[(y-1)*comprimento + x] == 1) // Encontrou uma semente no caminho para cima, não mover e virar semente
            {
                regiao[y*comprimento + x] = 1;
                if(y == 0)
                {
                    return true; // Caso uma gota vire semente no spawn, retorne True
                }
            }

            return false; // Qualquer outro caso que não seja uma gota virando semente no spawn, retorne False
        }

        bool MoveBaixo()
        {
            if(y == altura-1) // Na borda, logo o movimento faz sair da região
            {
                regiao[y*comprimento + x] = 0; // Zero representa que a gota foi destruida
            }
            else if(regiao[(y+1)*comprimento + x] == 0) // Nada no caminho, mover para baixo
            {
                regiao[(y+1)*comprimento + x] = 2;
                regiao[y*comprimento + x] = 0;
                y += 1;
            }
            else if(regiao[(y+1)*comprimento + x] == 1) // Encontrou uma semente no caminho para cima, não mover e virar semente
            {
                regiao[y*comprimento + x] = 1;
                if(y == 0)
                {
                    return true; // Caso uma gota vire semente no spawn, retorne True
                }
            }

            return false; // Qualquer outro caso que não seja uma gota virando semente no spawn, retorne False
        }


    public:
        Gota(): x(0) , y(0), comprimento(0), altura(0), regiao(nullptr){};
        Gota(int _x, int _y, int _comprimento, int _altura, int* _regiao): x(_x), y(_y), comprimento(_comprimento), altura(_altura), regiao(_regiao)
        {
            while(regiao[y*comprimento + x] == 2)
            {
                if(x == comprimento - 1)
                {
                    x = 0;
                }
                else
                {
                    x += 1;
                }
            }

            regiao[y*comprimento + x] = 2;
        };

        int getX() {return x;};
        void setX(int x) {this->x = x;};

        int getY() {return y;};
        void setY(int y) {this->y = y;};

        const int getcomprimento() {return comprimento;};
        const int getaltura() {return altura;};

        int* getRegiao() {return regiao;};

        bool MoveDirecao(int direcao)
        {
            if(direcao == 1)
                return MoveCima();
            else if(direcao == 2)
                return MoveDireita();
            else if(direcao == 3)
                return MoveBaixo();
            else if(direcao == 4)
                return MoveEsquerda();
            else
                return false;
        }

        Gota operator=(const Gota& obj)
        {
            this->x = obj.x;
            this->y = obj.y;
            this->regiao = obj.regiao;

            return *this;
        }

};


// Função para gerar a região com as sementes posicionadas
int* GerarRegiao(const int& comprimento, const int& altura)
{
    int* regiao = (int*) calloc(comprimento*altura, sizeof(int));
    int passo = round(comprimento/(comprimento*0.1));
    
    for(int i = 0; i < round(comprimento*0.1)+1; i++) // Quantidade de pontos é igual a 10% do comprimento
    {
        if(passo*i >= comprimento) // Caso o passo passe do comprimento da região
        {
            regiao[comprimento*(altura-1) + (comprimento-1)] = 1;
            break;
        }
        else
        {
            regiao[comprimento*(altura-1) + (passo*i)] = 1;
        }
    }

    return regiao;
}


int* ADL(const int& comprimento, const int& altura, const int& quantidadeGotasTela, const int& quantidadeGotasMaximas)
{
    // Inicialização e configurações
    int* regiao = GerarRegiao(comprimento, altura);
    bool isSementeInSpawn = false; // Não há semente no spawn no inicio
    int linhaSpawn = round(altura*0.9); // Escolher aonde a gota vai nascer
    int gotasTela = quantidadeGotasTela;
    int gotasMaximas = quantidadeGotasMaximas;
    vector<Gota> listaGotas;

    default_random_engine defEngine(time(nullptr));
    uniform_int_distribution<int> spawnGota(0, comprimento-1);
    uniform_int_distribution<int> direcaoMovimentacao(1, 4);

    if(gotasTela > comprimento)
    {
        gotasTela = comprimento;   
    }

    for(int i = 0; i < gotasTela; i++)
    {
        int x = spawnGota(defEngine);
        listaGotas.push_back(Gota(x, linhaSpawn, comprimento, altura, regiao));
        gotasMaximas -= 1;
    }

    cout << "Progresso 0%" << "\n";

    // Loop principal, Aqui que iremos ficar gerando as gotas até uma semente chegar na região de spawn
    // ou quando acabar as gotas
    while((!isSementeInSpawn) && (gotasMaximas > 0))
    {
        // Movimentação das particulas e verificar se alguma foi destruida
        for(int i = 0; i < listaGotas.size(); i++)
        {
            isSementeInSpawn = listaGotas[i].MoveDirecao(direcaoMovimentacao(defEngine));

            if(isSementeInSpawn)
            {
                return regiao; // Semente na região de Spawn final, logo finalizar a função retornando a região final
            }
                
            
            if(regiao[listaGotas[i].getY()*comprimento + listaGotas[i].getX()] == 0 || regiao[listaGotas[i].getY()*comprimento + listaGotas[i].getX()] == 1)
            {
                if(regiao[listaGotas[i].getY()*comprimento + listaGotas[i].getX()] == 1 && listaGotas[i].getY() == linhaSpawn)
                {
                    cout << "Progresso: " << (int) round(100 - 100*((float) linhaSpawn/altura)) << "%\n";
                    if(linhaSpawn < 0)
                    {
                        linhaSpawn = 0;
                    }      
                    else
                    {
                        linhaSpawn -= round(altura*0.1);
                    }
                }

                int x = spawnGota(defEngine);
                listaGotas[i] = Gota(x, linhaSpawn, comprimento, altura, regiao);
                gotasMaximas -= 1;
                continue;
            }
        }
    }

    return regiao;
}


// 0 representa vazio na região
// 1 representa semente na região
// 2 representa gota na região

// argumento 0 = nome do arquivo compilado
// argumento 1 = comprimento imagem
// argumento 2 = altura imagem
// argumento 3 = quantidade de gotas na tela
// argumento 4 = quantidade máxima de gotas geradas
int main(int argc, char** argv)
{
    // Não rodar o código caso não foi inicializado com os parâmetros corretos
    if(argc != 5)
    {
        return 0;
    }

    const int comprimento = abs(stoi(argv[1]));
    const int altura = abs(stoi(argv[2]));
    const int gotasTela = abs(stoi(argv[3]));
    const int gotasmaximas = abs(stoi(argv[4]));

    int* regiao = ADL(comprimento, altura, gotasTela, gotasmaximas);

    ofstream plote;
    plote.open("regiao.txt", ios::out);

    for(int i = 0; i < altura; i++)
    {
        for(int j = 0; j < comprimento; j++)
        {
            plote << regiao[i*comprimento + j] << " ";
        }
        plote << "\n";
    }

    plote.close();
    free(regiao);

    return 0;
}