#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    int id;
    int clienteId;
    int produtoId;
    int quantidade;
    float total;
    char data[20];
} Venda;

// funcao que gera os id 
int gerarId() {
    return rand() % 1000 + 1;
}

// funcao pra pegar a data inicial 
void pegarData(char *buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void cadastrarCliente() {
    Cliente c;
    FILE *f = fopen("clientes.txt", "a");

    if (f == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    c.id = gerarId();
    printf("Nome do cliente: ");
    scanf(" %[^\n]", c.nome);
    printf("CPF: ");
    scanf(" %[^\n]", c.cpf);

    fprintf(f, "%d %s %s\n", c.id, c.nome, c.cpf);
    fclose(f);

    printf("Cliente cadastrado com ID %d\n", c.id);
}

void cadastrarProduto() {
    Produto p;
    FILE *f = fopen("produtos.txt", "a");

    if (f == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        return;
    }

    p.id = gerarId();
    printf("Nome do produto: ");
    scanf(" %[^\n]", p.nome);
    printf("Preco: ");
    scanf("%f", &p.preco);
    printf("Estoque: ");
    scanf("%d", &p.estoque);

    fprintf(f, "%d %s %.2f %d\n", p.id, p.nome, p.preco, p.estoque);
    fclose(f);

    printf("Produto cadastrado com ID %d\n", p.id);
}

void registrarVenda() {
    Venda v;
    FILE *f = fopen("vendas.txt", "a");

    if (f == NULL) {
        printf("Erro ao abrir o arquivo de vendas.\n");
        return;
    }

    v.id = gerarId();
    printf("ID do cliente: ");
    scanf("%d", &v.clienteId);
    printf("ID do produto: ");
    scanf("%d", &v.produtoId);
    printf("Quantidade: ");
    scanf("%d", &v.quantidade);
    printf("Preco unitario: ");
    float precoUnitario;
    scanf("%f", &precoUnitario);

    v.total = v.quantidade * precoUnitario;
    pegarData(v.data);

    fprintf(f, "%d %d %d %d %.2f %s\n", v.id, v.clienteId, v.produtoId, v.quantidade, v.total, v.data);
    fclose(f);

    printf("Venda registrada com total R$ %.2f\n", v.total);
}

int main() {
    srand(time(NULL));
    int opcao;

    do {
        printf("\n=== MENU ===\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Cadastrar produto\n");
        printf("3 - Registrar venda\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                cadastrarProduto();
                break;
            case 3:
                registrarVenda();
                break;
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}
