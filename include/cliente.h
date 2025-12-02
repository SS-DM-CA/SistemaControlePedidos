#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct cliente {
    int id;                
    char endereco[201];
    char telefone[20];
    char email[101];
    char nome[201];
    char contato[101];
    char identidade[21];
} Cliente;

void modulo_clientes();
void cadastrarCliente();
void consultarCliente();
void removerCliente();
void listarClientes();

int analisaCliente(int Id, Cliente *clientes, int tamanhoCli);

#endif // CLIENTE_H