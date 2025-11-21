#include <stdio.h>
#include "produto.h"

int analisaProduto();

int main(){}

int analisaProduto(int id,Produto *produtos,int tamanhoProd) {
    for (int i = 0 ; i<tamanhoProd;i++) {
        if (id == produtos[i].id) {
            return 1;
        }
    }

    return 2;

}
//o int tamanhoProd é o tamnho do vetor produtos, devo definir essa variavel como parametro na persistencia
void cadastrarProduto(int id, Produto produto, Produto *produtos,int tamanhoProd) {
    printf("Digite o id do produto:");
    scanf("%d", &id);
    if (analisaProduto(id,produtos,tamanhoProd) == 1) {
        //produto ja existe
        return EXIT_FAILURE;
    }
    else {
        scanf("%99[^\n] %lf %d",produto.descricao,&produto.preco,&produto.estoque);
        //Quando ele apertar o botão Cadastrar
        produtos = (Produto *) realloc(produtos,(tamnhoProd+1)*sizeof(Produto));
    }

}