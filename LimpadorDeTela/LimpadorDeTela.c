/******************************************************************************

O objetivo do agente A é capturar todos os . e os * da tela no menor tempo possivel.
Os * são mais atrativos para o agente que os .
1 - Escreva a função do agente seguindo o modelo reativo simples.
2 - Escreva a função do agente seguindo o modelo reativo baseado em modelos.
3 - Escreva a função do agente seguindo o modelo reativo baseado em objetivos.
4 - Escreva a função do agente seguindo o modelo reativo baseado na utilidade.

Depois compare o tempo que cada abordagem demorou para atingir o objetivo.

O agente capta com seus sensores o conteudo das 4 casas ao seu redor (esquerda, direita, cima, baixo)
O agente tem como acoes movimentar-se para esquerda (0), direita (1), cima (2), baixo (3)

Obs.: A função de agente implementada como exemplo representa um agente aleatório,
qualquer abordagem que você desenvolver, deve ser no mínimo melhor que o aleatório.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 36

int posAgenteX = 1;
int posAgenteY = 1;
int posAgentAnterior = 0;

int ambiente[SIZE][SIZE];

void delay(int tempo){
	for(int i=0; i<tempo; i++);
}

void construirAmbiente(){
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
			if(i == 0 || i == SIZE-1){
				if(j == 0 || j == SIZE-1) ambiente[i][j] = 3;
				else ambiente[i][j] = 4;
			}
			else if(j == 0 || j == SIZE-1) ambiente[i][j] = 5;
			else ambiente[i][j] = rand()%3;
		}
	}
}

void atualizarAmbiente(int acao){
    ambiente[posAgenteX][posAgenteY] = 0;
    if (acao == 0 && ambiente[posAgenteX][posAgenteY-1] < 3) posAgenteY -= 1;
    else if (acao == 1 && ambiente[posAgenteX][posAgenteY+1] < 3) posAgenteY += 1;
    else if (acao == 2 && ambiente[posAgenteX-1][posAgenteY] < 3) posAgenteX -= 1;
    else if (acao == 3 && ambiente[posAgenteX+1][posAgenteY] < 3) posAgenteX += 1;
    ambiente[posAgenteX][posAgenteY] = 6;
}

void mostrarAmbiente(){
	system("cls");
	int count = 0;
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            if (ambiente[i][j] == 0) printf(" ");
            else if (ambiente[i][j] == 1) { count++; printf(".");}
            else if (ambiente[i][j] == 2) { count++; printf("*");}
            else if (ambiente[i][j] == 3) printf("+");
            else if (ambiente[i][j] == 4) printf("-");
            else if (ambiente[i][j] == 5) printf("|");
            else if (ambiente[i][j] == 6) printf("A");
        }
        printf("\n");
    }
	printf("Faltam %d objetos.\n", count);
}

bool verificarSucesso(){
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            if (ambiente[i][j] == 1 || ambiente[i][j] == 2) return false;
        }
    }
    return true;
}

int lerSensor(int lado){
    if (lado == 0) return ambiente[posAgenteX][posAgenteY-1];
    if (lado == 1) return ambiente[posAgenteX][posAgenteY+1];
    if (lado == 2) return ambiente[posAgenteX-1][posAgenteY];
    if (lado == 3) return ambiente[posAgenteX+1][posAgenteY];
    return 2;
}

int funcaoAgente(int esquerda, int direita, int cima, int baixo){
        // 0 = ESQUERDA
        // 1 = DIREITA
        // 2 = CIMA
        // 3 = BAIXO

        // 1 = .
        // 2 = *

    //Caso ele já tenha ido pra esquerda
	if (posAgentAnterior == 0){

        if(direita == 2){
            if (cima == 2){
                posAgentAnterior = 2;
                return 2;
            } else if(baixo == 2){
                posAgentAnterior = 3;
                return 3;
            }else{
                posAgentAnterior = 1;
                return 1;
            }


        }else if(direita == 1){
            if (cima == 2){
                posAgentAnterior = 2;
                return 2;
            }else if (baixo == 2){
                posAgentAnterior = 3;
                return 3;
            } else {
                posAgentAnterior = 1;
                return 1;
            }



        } else {
            if(cima == 2){
                posAgentAnterior = 2;
                return 2;
            }else if(cima == 1){
                if (baixo == 2){
                    posAgentAnterior = 3;
                    return 3;
                } else {
                    posAgentAnterior = 2;
                    return 2;
                }

            }else{

                if(baixo == 2){
                    posAgentAnterior = 3;
                    return 3;
                }else if(baixo == 1){
                    posAgentAnterior = 3;
                    return 3;
                }else{
                    return rand()%4;
                }

            }

        }
	}

    // Caso ele já tenha ido pra direita
    if (posAgentAnterior == 1){
        if (esquerda == 2){
            if (cima == 2){
                posAgentAnterior = 2;
                return 2;
            }else if(baixo == 2){
                posAgentAnterior = 3;
                return 3;
            }else{
                posAgentAnterior = 0;
                return 0;
            }

        }else if (esquerda == 1){
            if (cima == 2){
                posAgentAnterior = 2;
                return 2;
            }else if (baixo == 2){
                posAgentAnterior = 3;
                return 3;
            } else {
                posAgentAnterior = 0;
                return 0;
            }

        }else {
            if(cima == 2){
                posAgentAnterior = 2;
                return 2;
            }else if(cima == 1){

                if (baixo == 2){
                    posAgentAnterior = 3;
                    return 3;
                } else {
                    posAgentAnterior = 2;
                    return 2;
                }

            }else{

                if(baixo == 2){
                    posAgentAnterior = 3;
                    return 3;
                }else if(baixo == 1){
                    posAgentAnterior = 3;
                    return 3;
                }else{
                    return rand()%4;
                }

            }

        }

    }


    //Caso ele já tenha ido pra cima
    if ( posAgentAnterior == 2){

        if( esquerda == 2){
            if(direita == 2){
                posAgentAnterior = 1;
                return 1;
            }else if( baixo == 2){
                posAgentAnterior = 3;
                return 3;
            }else{
                posAgentAnterior = 0;
                return 0;
            }


        }else if(esquerda == 1){
            if(direita == 2){
                posAgentAnterior = 1;
                return 1;
            }else if( baixo == 2){
                posAgentAnterior = 3;
                return 3;
            }else{
                posAgentAnterior = 1;
                return 1;
            }
        }else{
            if(direita == 2){
                if(baixo == 2){
                    posAgentAnterior = 3;
                    return 3;
                } else {
                    posAgentAnterior = 1;
                    return 1;
                }

            } else if(direita == 1){

                if (baixo == 2 ){
                    posAgentAnterior = 3;
                    return 3;
                } else {
                    posAgentAnterior = 1;
                    return 1;
                }

            }else {

                if (baixo == 2 ){
                    posAgentAnterior = 3;
                    return 3;
                }else if(baixo == 1){
                    posAgentAnterior = 3;
                    return 3;
                } else {
                    return rand()%4;
                }
            }
        }
    }

    //Caso ele já tenha ido pra baixo
    if (posAgentAnterior == 3){
            if( cima == 2 ){
                if(direita == 2){
                    posAgentAnterior = 1;
                    return 1;
                }else if (esquerda == 2){
                    posAgentAnterior = 0;
                    return 0;
                }else{
                    posAgentAnterior = 2;
                    return 2;
                }
            }else if (cima == 1){
                if(direita == 2){
                    posAgentAnterior = 1;
                    return 1;
                }else if (esquerda == 2){
                    posAgentAnterior = 0;
                    return 0;
                }else{
                    posAgentAnterior = 2;
                    return 2;
                }
            }else{
                if (esquerda == 2){
                    if(direita == 2){
                        posAgentAnterior = 1;
                        return 1;
                    }else{
                        posAgentAnterior = 0;
                        return 0;
                    }
                }else if(esquerda == 1){
                    if(direita == 2){
                        posAgentAnterior = 1;
                        return 1;
                    }else{
                        posAgentAnterior = 0;
                        return 0;
                    }
                }else{
                    posAgentAnterior = 1;
                    return 1;
                }

            }


    }


        return rand()%4;
    }


int main()
{
    clock_t tempo[2];
	construirAmbiente();
	mostrarAmbiente();

    tempo[0] = clock();
	while(!verificarSucesso()){
        int acao = funcaoAgente(lerSensor(0), lerSensor(1), lerSensor(2), lerSensor(3));
        atualizarAmbiente(acao);
        mostrarAmbiente(); //mostra o que esta acontecendo, mas atrasa a execução
    }
	tempo[1] = clock();

	printf("Tempo gasto: %g ms.", ((tempo[1] - tempo[0]) / ((double)CLOCKS_PER_SEC)));
    return 0;
}
