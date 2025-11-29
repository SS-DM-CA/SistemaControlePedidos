#ifndef  PRODUTO_H
#define  PRODUTO_H

typedef struct {
    int id;
    char descricao[100];
    double preco;
    int estoque;
}Produto;

void cadastrarProduto(Produto produto,Produto *produtos,int tamanhoProd);

void consultarProduto( Produto *produtos, int tamanhoProd);

void removerProduto(Produto *produtos, int tamanhoProd);

void listarProdutos(Produto *produtos, int tamanhoProd);






#endif //PRODUTO_H
