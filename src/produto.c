#include <stdio.h>
#include "..include/produto.h"

int analisaProduto(int Id,Produto *produtos,int tamanhoProd);

int main(){}

void removerProduto(Produto **produtos, int *tamanhoProd,ItemPedido *itemsPedidos, int tamanhoItemPed) {
    int Id;
    printf("Digite o id do produto:");
    scanf("%d", &Id);
    if (analisaProduto(Id,*produtos,*tamanhoProd) == 2) {
        //O produto não existe
        return EXIT_FAILURE;
        printf("O produto não existe");
    }
    else {
        //verificar se tem algum pedido que contenha essa produto
        for (int i =0;i<tamanhoItemPed;i++) {
            if (itemsPedido[i].produtoId == Id) {
                //existe um pedido com esse produto
                printf("Esse produto nao podera ser excluido");
                break;
            }
            else {
                //confirmar se o usuario deseja ou não remover o produto
                char confirmacao;
                printf("Deseja comfirmar a exclusao do produto: (s)para sim e (n)para nao");
                scanf("%c",&confirmacao);
                //ele quer remover o produto
                if (confirmacao == "s") {
                    //remover produto
                    for (int i=0;i<*tamanhoProd;i++) {
                        if (*produtos[i].id==Id) {
                            for (int j =i;j<*tamanhoProd-1;j++) {
                                *produtos[j] = *produtos[j+1];
                            }
                            //diminui o tamanho do vetor
                            *produtos= (Produto *) realloc(*produtos,(*tamanhoProd-1)*sizeof(Produto));
                            (*tamanho)--;
                            break;
                        }
                    }
                }
                break;
                //ele não quer remover  o produto
                else if (confirmacao == "n") {
                    printf("A remocao do produto foi cancelada");
                    break;
                }
            }
        }
        //Produto exite






    }
}

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
void cadastrarProduto (Produto produto, Produto **produtos,int *tamanhoProd) {
    int Id;
    printf("Digite o id do produto:");
    scanf("%d", &Id);
    if (analisaProduto(Id,produtos,tamanhoProd) == 1) {
        //produto ja existe
        return EXIT_FAILURE;
    }
    else {
        //Produto ainda não existe
        //o campo id do struct Produto recebe o id digitado pelo usuario
        produto.id = Id;
        //Digite os valores do produto
        scanf("%99[^\n] %lf %d",produto.descricao,&produto.preco,&produto.estoque);
        //Quando ele apertar o botão Cadastrar
        //aumenta a posição do vetor
        *produtos = (Produto *) realloc(*produtos,(*tamnhoProd+1)*sizeof(Produto));
        //adiciona os valores no vetor
        *produtos[*tamanhoProd] = produto;
        //aumenta um no tamanho
        (*tamanhoProd)++;
    }

}

void consultarProduto(Produto *produtos, int tamanhoProd ) {
    int Id;
    printf("Digite o id do produto:");
    scanf("%d", &Id);
    if (analisaProduto(Id,produtos,tamanhoProd) == 2) {
        //produto não existe
        //colocar mensagem de erro informando que o produto não existe
        printf("Não existe esse produto");
        return EXIT_FAILURE;

    }
    else {
        //Produto existe
        for (int i =0; i<tamanhoProd; i++) {
            if (produtos[i].id == Id ) {
                //imprimir os dados do produto
                printf("%d,%99[^\n],%lf,%d ", produtos[i].id,produtos[i].descricao,produtos[i].preco,produtos[i].estoque);
                break;
            }
        }
    }

}

void listarProduto (Produto *produtos,int tamanhoProd) {
    for (int i =0; i<tamanhoProd;i++) {
        printf("%d,%99[^\n],%lf,%d ", produtos[i].id,produtos[i].descricao,produtos[i].preco,produtos[i].estoque);
    }
}




