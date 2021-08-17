/*
********************************************************
            Felipe Augusto Lee   RA: 240262
            Matéria: Estrutura de Dados 1
            Professor: Rodrigo Minetto
                DAINF   -   UTFPR

            Trabalho sobre Ciclo Hamiltoniano
********************************************************
O Objetivo do código é de verificar se um dado ciclo é ou não hamiltoniano e propor um dos possíveis caminhos.
Isso é feito por meio do uso de Back-Tracking para tentar achar um caminho, testando todos eles.

Alguns nomes de variáveis:
mconex[][] = Matriz de Conexões (Mostra as conexões entre os vértices, 1 se há, 0 se não há)
vcaminho[] = Vetor de Caminho (representa os passos do ciclo, nesse caso começamos no vértice 0, os passos ainda não preenchidos = -1)
pos = posição no vetor de caminho que estamos tratando no momento
tam = tamanho do vetor de caminho e da matriz de conexões
*/

#include<stdio.h>

int pode_incluir(int i, int tam, int mconex[][tam], int vcaminho[], int pos){

    //Verifica se tal vértice já foi visitado
    for(int j=0 ; j<tam ; j++){
        if( vcaminho[j] == i )
            return 0;
    }

    //Verifica se há conexão entre o vértice já posto ( caminhp[pos-1] ) e o novo que queremos adicionar ( i )
    if( ! mconex[ vcaminho[pos-1] ][ i ] )
        return 0;

    //Se não falhou em nenhuma desses requisitoes, então pode ser adicionado
    return 1;
}

//Uso de Back-Tracking
int verifica_CicloHamiltoniano(int tam, int mconex[][tam], int vcaminho[], int pos){

    //Verifica se já conseguiu preencher o vetor de caminho, e então, se é válido.
    if(pos == tam){
        //verifica se há conexão entre o último e o primeiro para fechar o ciclo. (como estamos usando 1 e 0, é só retorna-los)
        return mconex[ vcaminho[pos-1] ][ vcaminho[0] ];    
    }

    //caso o caminho ainda não tenha sido preenchido
    //vou "tentar ir à todos os outros vértices" para achar um caminho de sucesso
    for(int i=0 ; i<tam ; i++){
        //Se puder incluir i no vetor de caminho
        if( pode_incluir(i, tam, mconex, vcaminho, pos) ){
            vcaminho[pos] = i;  //lembrar que eu preciso colocá-lo no vetor antes da próxima chamada da função para que seja possível comparar a conexão desse com o próximo
            
            if( verifica_CicloHamiltoniano(tam, mconex, vcaminho, pos+1) )
                return 1;
            
            //se não foi possível chegar a um caminho, retorna até aqui para tentar um novo (pois está num loop tentando todos os vértices)
            vcaminho[pos] = -1;            
        }

    }

    //se o programa conseguiu chegar aqui, significa que, após testar todos os caminhos possíveis, não foi possível achar um ciclo
    return 0;
}

void imprimir_caminho(int tam, int vcaminho[]){
    printf("Um dos caminhos possíveis:\n");

    for( int i=0 ; i<tam ; i++)
        printf("%d -> ", vcaminho[i]);

    printf("%d\n", vcaminho[0]);
}

int main(){

    int tam = 5;

    int vcaminho[tam];
    for( int i=0 ; i<tam ; i++)
        vcaminho[i] = -1;
    vcaminho[0] = 0;    //aqui inicializamos o caminho no vértice 0

    int mconex[5][5] = { {0, 1, 1, 0, 1}, {1, 0, 1, 1, 1}, {1, 1, 0, 1, 0}, {0, 1, 1, 0, 1}, {1, 1, 0, 1, 0} };
    //int mconex[5][5] = { {0, 1, 0, 0, 1}, {1, 0, 1, 1, 1}, {0, 1, 0, 1, 0}, {0, 1, 1, 0, 0}, {1, 1, 0, 0, 0} };
    //int mconex[5][5] = { {0, 0, 0, 1, 1}, {0, 0, 0, 1, 1}, {0, 0, 0, 1, 1}, {1, 1, 1, 0, 0}, {1, 1, 1, 0, 0} };
    //int mconex[5][5] = { {0, 1, 1, 1, 0}, {1, 0, 1, 0, 0}, {1, 1, 0, 0, 0}, {1, 0, 0, 0, 1}, {0, 0, 0, 1, 0} };


    if( verifica_CicloHamiltoniano(tam, mconex, vcaminho, 1) ){
        printf("O Ciclo eh Hamiltoniano!\n");
        imprimir_caminho(tam, vcaminho);
    }
    else
        printf("O Ciclo NAO eh Hamiltoniano!\n");

    return 0;
}