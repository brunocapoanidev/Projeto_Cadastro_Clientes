#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100


typedef struct {
    int id;
    char nome[50];
    char cpf[20];
} Cliente;

typedef struct {
    int id;
    char nome[50];
    float preco;
    int estoque;
} Produto;

typedef struct {
    int produtoId;
    int quantidade;
    float valorUnitario;
} ItemVenda;

typedef struct {
    int id;
    int clienteId;
    char data[20];
    ItemVenda itens[10];
    int totalItens;
    float total;
} Venda;

int gerarId() {
    return rand() % 10000 + 1;
}

void dataAtual(char* buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}


void cadastrarCliente() {
    Cliente c;
    FILE *f = fopen("clientes.txt", "a");

    c.id = gerarId();
    printf("Nome: ");
    scanf(" %[^\n]", c.nome);
    printf("CPF: ");
    scanf(" %[^\n]", c.cpf);

    fprintf(f, "%d|%s|%s\n", c.id, c.nome, c.cpf);
    fclose(f);
    printf("Cliente cadastrado com ID: %d\n", c.id);
}

void cadastrarProduto() {
    Produto p;
    FILE *f = fopen("produtos.txt", "a");

    p.id = gerarId();
    printf("Nome: ");
    scanf(" %[^\n]", p.nome);
    printf("Preco: ");
    scanf("%f", &p.preco);
    printf("Estoque: ");
    scanf("%d", &p.estoque);

    fprintf(f, "%d|%s|%.2f|%d\n", p.id, p.nome, p.preco, p.estoque);
    fclose(f);
    printf("Produto cadastrado com ID: %d\n", p.id);
}


void cadastrarVenda() {
    Venda v;
    FILE *f = fopen("vendas.txt", "a");

    v.id = gerarId();
    printf("ID do cliente: ");
    scanf("%d", &v.clienteId);

    dataAtual(v.data);
    v.total = 0.0;
    printf("Quantos itens na venda? ");
    scanf("%d", &v.totalItens);

    for (int i = 0; i < v.totalItens; i++) {
        printf("Produto ID: ");
        scanf("%d", &v.itens[i].produtoId);
        printf("Quantidade: ");
        scanf("%d", &v.itens[i].quantidade);
        printf("Valor unitario: ");
        scanf("%f", &v.itens[i].valorUnitario);

        v.total += v.itens[i].quantidade * v.itens[i].valorUnitario;
    }

    fprintf(f, "%d|%d|%s|%.2f|", v.id, v.clienteId, v.data, v.total);
    for (int i = 0; i < v.totalItens; i++) {
        fprintf(f, "%d,%d,%.2f;", v.itens[i].produtoId, v.itens[i].quantidade, v.itens[i].valorUnitario);
    }
    fprintf(f, "\n");

    fclose(f);
    printf("Venda registrada com total R$ %.2f\n", v.total);
}


int main() {
    srand(time(NULL));
    int opcao;

    do {
        printf("\n====== MENU ======\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Cadastrar Produto\n");
        printf("3. Registrar Venda\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: cadastrarCliente(); break;
            case 2: cadastrarProduto(); break;
            case 3: cadastrarVenda(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
