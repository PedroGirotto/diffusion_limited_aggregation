class Gota():
    def __init__(self, regiao, x:int, y:int):
        self.x = x
        self.y = y
        self.regiao = regiao

        while(self.regiao[self.y, self.x] == 2): # Caso o local já tenha uma gota, mova para direita
            if(self.x == regiao.shape[1]-1): # Caso haja uma particula na borda direita, volta para borda esquerda
                self.x = 0
            else:
             self.x += 1
        
        self.regiao[self.y, self.x] = 2

    def MoveDireita(self):
        if(self.x == self.regiao.shape[1] - 1): # Na borda, logo o movimento faz sair da região
            self.regiao[self.y, self.x] = 0 # Zero representa que a gota foi destruida
        elif(self.regiao[self.y, self.x + 1] == 0): # Nada no caminho, mover para direita
            self.regiao[self.y, self.x + 1] = 2
            self.regiao[self.y, self.x] = 0
            self.x += 1
        elif(self.regiao[self.y, self.x + 1] == 1): # Encontrou uma semente no caminho para direita, não mover e virar semente
            self.regiao[self.y, self.x] = 1
            if(self.y == 0):
                return True # Caso uma gota vire semente no spawn, retorne True
        return False # Qualquer outro caso que não seja uma gota virando semente no spawn, retorne False

    def MoveEsquerda(self):
        if(self.x == 0): # Na borda, logo o movimento faz sair da região
            self.regiao[self.y, self.x] = 0 # Zero representa que a gota foi destruida
        elif(self.regiao[self.y, self.x - 1] == 0): # Nada no caminho, mover para esquerda
            self.regiao[self.y, self.x - 1] = 2
            self.regiao[self.y, self.x] = 0
            self.x -= 1
        elif(self.regiao[self.y, self.x - 1] == 1): # Encontrou uma semente no caminho para esquerda, não mover e virar semente
            self.regiao[self.y, self.x] = 1
            if(self.y == 0):
                return True # Caso uma gota vire semente no spawn, retorne True
        return False # Qualquer outro caso que não seja uma gota virando semente no spawn, retorne False

    def MoveCima(self):
        if(self.y == 0): # Na borda, logo o movimento faz sair da região
            self.regiao[self.y, self.x] = 0 # Zero representa que a gota foi destruida
        elif(self.regiao[self.y - 1, self.x] == 0): # Nada no caminho, mover para cima
            self.regiao[self.y - 1, self.x] = 2
            self.regiao[self.y, self.x] = 0
            self.y -= 1 
        elif(self.regiao[self.y - 1, self.x] == 1): # Encontrou uma semente no caminho para cima, não mover e virar semente
            self.regiao[self.y, self.x] = 1
            if(self.y == 0):
                return True # Caso uma gota vire semente no spawn, retorne True
        return False # Qualquer outro caso que não seja uma gota virando semente no spawn, retorne False

    def MoveBaixo(self):
        if(self.y == self.regiao.shape[0] - 1): # Na borda, logo o movimento faz sair da região
            self.regiao[self.y, self.x] = 0 # Zero representa que a gota foi destruida
        elif(self.regiao[self.y + 1, self.x] == 0): # Nada no caminho, mover para baixo
            self.regiao[self.y + 1, self.x] = 2
            self.regiao[self.y, self.x] = 0
            self.y += 1
        elif(self.regiao[self.y + 1, self.x] == 1): # Encontrou uma semente no caminho para baixo, não mover e virar semente
            self.regiao[self.y, self.x] = 1
            if(self.y == 0):
                return True # Caso uma gota vire semente no spawn, retorne True
        return False # Qualquer outro caso que não seja uma gota virando semente no spawn, retorne False

    def MoveDirecao(self, direcao:int):
        if(direcao == 1):
            return self.MoveCima()
        elif(direcao == 2):
            return self.MoveDireita()
        elif(direcao == 3):
            return self.MoveBaixo()
        elif(direcao == 4):
            return self.MoveEsquerda()
# CLASSE GOTA - Ok (?)


def GerarRegiao(comprimento: int, altura:int):
    # Função para gerar a região com as sementes posicionadas
    regiao = np.zeros((altura, comprimento), np.int8)
    passo = round(comprimento/(comprimento*0.1))
    for i in range(round(comprimento*0.1)+1): # Quantidade de pontos é igual a 10% do comprimento
        if(passo*i >= comprimento): # Caso o passo passe do comprimento da região
            regiao[-1, -1] = 1
            break
        else:
            regiao[-1, passo*i] = 1

    return regiao
# GERARREGIAO - OK


def ADL(comprimento: int, altura: int, quantidadeGotasTela:int, quantidadeGotasMaximas:int):  
    # Inicialização e configurações
    regiao = GerarRegiao(comprimento, altura)
    isSementeInSpawn = False # Não há semente no spawn no inicio
    linhaSpawn = round(altura*0.9) # Escolher aonde a gota vai nascer
    
    if(quantidadeGotasTela > comprimento): # Evitar criar quantidade de gotas maior que o spawn
        quantidadeGotasTela = comprimento

    listaGotas = []
    for _ in range(quantidadeGotasTela):
        listaGotas.append(Gota(regiao, randint(0, comprimento-1), linhaSpawn))  ### teste de nascer mais no meio
        quantidadeGotasMaximas -= 1

    print("Progresso: 0%")

    # Loop principal, Aqui que iremos ficar gerando as gotas até uma semente chegar na região de spawn
    # ou quando acabar as gotas
    while(not isSementeInSpawn and quantidadeGotasMaximas):
        # Movimentação das particulas e verificiar se alguma foi destruida
        for i in range(quantidadeGotasTela):
            # Faz a movimentação e retorna se uma semente está no spawn
            isSementeInSpawn = listaGotas[i].MoveDirecao(randint(1, 4))
            if(isSementeInSpawn):
                break
            if(regiao[listaGotas[i].y, listaGotas[i].x] == 0 or regiao[listaGotas[i].y, listaGotas[i].x] == 1):
                listaGotas[i] = 0

        if(0 in listaGotas):
            for i in range(quantidadeGotasTela):
                if(listaGotas[i] == 0):
                    listaGotas[i] = Gota(regiao, randint(0, comprimento-1), linhaSpawn)
                    quantidadeGotasMaximas -= 1

        if(1 in regiao[linhaSpawn,:]):
            print(f"Progresso: {round(100 - 100*(linhaSpawn/altura))}%")
            if(linhaSpawn <= 0):
                linhaSpawn = 0
            else:
                linhaSpawn -= round(altura*0.1)

    return regiao
#ADL - Ok


if __name__ == "__main__":
    import numpy as np
    import matplotlib.pyplot as plt
    from random import randint
    import sys
   
    argumentos = []
    for i in range(1, len(sys.argv)):
        argumentos.append(int(sys.argv[i]))

    regiao = ADL(argumentos[0], argumentos[1], argumentos[2], argumentos[3])

    #Plot da região
    fig, ax = plt.subplots()
    ax.matshow(regiao, cmap = "inferno")
    plt.show()

    exit()