struct fisica{
    char nome[101];
    char celular[15];
    char cpf[12];
};

struct juridica{
    char razao[201];
    char contato[101];
    char cnpj[15];
};

struct cliente
{
    int identificador;
    char rua[101];
    char setor[51];
    char cidade[51];
    char estado[3];
    char telefone[15];
    char email[101];
    union{
        struct fisica pf;
        struct juridica pj;
    };
};
