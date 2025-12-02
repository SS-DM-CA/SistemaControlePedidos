#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct {
    int id;
    char descricao[100];
    double preco;
    int estoque;
} Produto;

void modulo_produtos();
void cadastrarProduto();
void consultarProduto();
void removerProduto();
void listarProduto();

int analisaProduto(int Id, Produto *produtos, int tamanhoProd);

#endif // PRODUTO_H