#include <stdio.h>
#include "..include/produto.h"

int analisaProduto();

int main(){}

int analisaProduto(int Id,Produto *produtos,int tamanhoProd) {
    for (int i = 0 ; i<tamanhoProd;i++) {
        if (Id == produtos[i].id) {
            //retorna 1 se o produto ja existir
            return 1;
        }
    }
    //retorna 2 se o produto não existir
    return 2;

}
//o int tamanhoProd é o tamnho do vetor produtos, devo definir essa variavel como parametro na persistencia
void cadastrarProduto(int Id, Produto produto, Produto *produtos,int tamanhoProd) {
    printf("Digite o id do produto:");
    scanf("%d", &Id);
    if (analisaProduto(Id,produtos,tamanhoProd) == 1) {
        //produto ja existe
        return EXIT_FAILURE;
    }
    else {
        produto.id = Id;
        scanf("%99[^\n] %lf %d",produto.descricao,&produto.preco,&produto.estoque);
        //Quando ele apertar o botão Cadastrar
        produtos = (Produto *) realloc(produtos,(tamnhoProd+1)*sizeof(Produto));
    }

}

void consultarProduto(int Id,Produto *produtos, int tamanhoProd ) {
    printf("Digite o id do produto:");
    scanf("%d", &Id);
    if (analisaProduto(Id,produtos,tamanhoProd) == 2) {
        //produto não existe
        //colocar mensagem de erro informando que o produto não existe
        return EXIT_FAILURE;
    }
    else {
        for (int i =0; i<tamanhoProd; i++) {
            if (produtos[i].id == Id ) {
                //imprimir os dados do produto
                printf("%d,%99[^\n],%lf,%d ", produtos[i].id,produtos[i].descricao,produtos[i].preco,produtos[i].estoque);
                break;
            }
        }
    }

}



