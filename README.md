# Diffusion-limited-aggregation

Diretriz do Projeto 01 da disciplina Laboratório de Programação Avançada do curso de Ciência da Computação da Instituição de Ensino Superior Cesupa.

## Introdução:
Agregação Limitada por Difusão (ALD) é um modelo de crescimento de mecânica estatística que foi introduzido por Witten e Sander (1981) e possui a seguinte definição.
Uma primeira partícula é fixa. Então, uma segunda partícula é liberada “no infinito” e realiza um passeio aleatório simétrico. Assim que toca a primeira partícula, ele para e gruda nela. Em seguida, liberamos outra partícula, que também vai grudar no aglomerado (o conjunto das partículas do agregado), e assim sucessivamente. . . Após um grande número de iterações, obtém-se um cluster com aparência de fractal.

O ALD não apenas modela partículas aderentes, mas também fluxo de Hele-Shaw (Shraiman e Bensimon, 1984), crescimento dendrítico (Vicsek, 1992) e ruptura dielétrica (Brady e Ball, 1984).

## Atividade:
O projeto é desenvolver uma ALD, em python, que segue a seguintes características:
- Teremos uma matriz ou uma região de renderização.
- A primeira linha da matriz é reservada para a região de spawn da partícula de movimento aleatório (chamaremos de gota).
- A ultima linha é reservada para as partículas fixas (chamaremos de semente), porém a quantidade de sementes é igual a 10% do comprimento da matriz e elas devem ser equidistantes entre si (não podemos ter semente nas borda esquerda e direita da matriz).
- Uma gota pode se movimentar tanto para cima, para baixo, para esquerda ou para direita. Quando uma gota toca em uma semente, ela para de se mover e se torna uma nova semente. Caso a gota "saia" da matriz, ela será destruída.

Para esse projeto teremos os seguintes parâmetros de entrada:
- Comprimento e altura da matriz ou região de renderização.
- Quantidade máxima de gotas se movimentando na nossa região, isso limita a quantidade de gotas que poderão está dentro da região.
- Quantidade máxima de gotas que serão criadas no decorrer do código, isso significa que em um momento ficaremos sem "água" para criar mais gotas.

Teremos as seguintes condições de paradas para a nossa aplicação:
- Quando uma semente chega na região de spawn.
- Quando acabar todas as gotas.

No final a aplicação deve retornar uma imagem ou animação do resultado.Fica livre a utilização de qualquer biblioteca para o desenvolvimento do projeto.

## Entrega:
O dia para a entrega do projeto é até o dia 29/03 e deve ser feito o upload do código ou postar o link do repositório.
