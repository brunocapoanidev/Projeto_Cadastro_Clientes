#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototipos
int registrar_cliente();
int registrar_produto();
int registrar_venda();
void mostrar_clientes();
void mostrar_produtos();
void remover_cliente();
void remover_produto();
void atualizar_cliente();
void atualizar_produto();
void listar_vendas();
void produto_top_vendas();

// Estruturas
typedef struct {
    int codigo;
    char nome[50];
    char cpf[12];
    int idade;
} Cliente;

typedef struct {
    int codigo;
    char nome[50];
    float preco;
    int quantidade_vendida;
} Produto;

typedef struct {
    int id_venda;
    int id_cliente;
    int itens[10];
    int qtds[10];
    int total_itens;
    float valor_final;
    int forma_pagamento;
} Venda;

// Arrays globais
Cliente clientes[10];
Produto produtos[10];
Venda vendas[50];

// Contadores e IDs
int total_clientes = 0;
int total_produtos = 0;
int total_vendas = 0;
int prox_cliente_id = 1;
int prox_produto_id = 1;
int prox_venda_id = 1;

int main() {
    int opcao;

    do {
        printf("\n=========== MENU PRINCIPAL ===========\n");
        printf("0 - Sair\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Cadastrar Produto\n");
        printf("3 - Realizar Venda\n");
        printf("4 - Listar Clientes\n");
        printf("5 - Listar Produtos\n");
        printf("6 - Excluir Cliente\n");
        printf("7 - Excluir Produto\n");
        printf("8 - Editar Cliente\n");
        printf("9 - Editar Produto\n");
        printf("10 - Listar Vendas\n");
        printf("11 - Produto mais vendido\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: registrar_cliente(); break;
            case 2: registrar_produto(); break;
            case 3: registrar_venda(); break;
            case 4: mostrar_clientes(); break;
            case 5: mostrar_produtos(); break;
            case 6: remover_cliente(); break;
            case 7: remover_produto(); break;
            case 8: atualizar_cliente(); break;
            case 9: atualizar_produto(); break;
            case 10: listar_vendas(); break;
            case 11: produto_top_vendas(); break;
            case 0: printf("Encerrando o sistema...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}

int registrar_cliente() {
    if(total_clientes >= 10) {
        printf("Limite de clientes atingido.\n");
        return 0;
    }

    Cliente novo;
    novo.codigo = prox_cliente_id++;
    printf("\nNome do cliente: ");
    scanf("%s", novo.nome);
    printf("Idade: ");
    scanf("%d", &novo.idade);
    printf("CPF (somente numeros): ");
    scanf("%s", novo.cpf);

    clientes[total_clientes++] = novo;
    printf("Cliente registrado com sucesso! Codigo: %d\n", novo.codigo);

    char resp;
    printf("Cadastrar outro cliente? (s/n): ");
    scanf(" %c", &resp);
    if(resp == 's' || resp == 'S') {
        return registrar_cliente();
    }
    return 1;
}

int registrar_produto() {
    if(total_produtos >= 10) {
        printf("Limite de produtos atingido.\n");
        return 0;
    }

    Produto novo;
    novo.codigo = prox_produto_id++;
    novo.quantidade_vendida = 0;

    printf("\nNome do produto: ");
    scanf("%s", novo.nome);
    printf("Preco unitario: ");
    scanf("%f", &novo.preco);

    produtos[total_produtos++] = novo;
    printf("Produto cadastrado com codigo %d.\n", novo.codigo);

    char resp;
    printf("Cadastrar outro produto? (s/n): ");
    scanf(" %c", &resp);
    if(resp == 's' || resp == 'S') {
        return registrar_produto();
    }
    return 1;
}

int registrar_venda() {
    if(total_vendas >= 50) {
        printf("Limite de vendas atingido.\n");
        return 0;
    }

    Venda v;
    v.id_venda = prox_venda_id++;
    v.total_itens = 0;
    v.valor_final = 0;

    printf("\nSelecionar cliente:\n");
    mostrar_clientes();
    printf("Digite o codigo do cliente: ");
    scanf("%d", &v.id_cliente);

    int cliente_encontrado = 0;
    for(int i=0; i<total_clientes; i++) {
        if(clientes[i].codigo == v.id_cliente) {
            cliente_encontrado = 1;
            break;
        }
    }
    if(!cliente_encontrado) {
        printf("Cliente nao encontrado.\n");
        return 0;
    }

    char cont = 's';
    while((cont == 's' || cont == 'S') && v.total_itens < 10) {
        mostrar_produtos();
        printf("Codigo do produto: ");
        scanf("%d", &v.itens[v.total_itens]);

        int prod_index = -1;
        for(int i=0; i<total_produtos; i++) {
            if(produtos[i].codigo == v.itens[v.total_itens]) {
                prod_index = i;
                break;
            }
        }
        if(prod_index == -1) {
            printf("Produto nao encontrado.\n");
            continue;
        }

        printf("Quantidade: ");
        scanf("%d", &v.qtds[v.total_itens]);

        v.valor_final += produtos[prod_index].preco * v.qtds[v.total_itens];
        produtos[prod_index].quantidade_vendida += v.qtds[v.total_itens];
        v.total_itens++;

        if(v.total_itens < 10) {
            printf("Adicionar mais produtos? (s/n): ");
            scanf(" %c", &cont);
        }
    }

    if(v.total_itens == 0) {
        printf("Venda cancelada (nenhum produto).\n");
        return 0;
    }

    printf("Forma de pagamento (1-dinheiro, 2-pix, 3-cartao): ");
    scanf("%d", &v.forma_pagamento);

    vendas[total_vendas++] = v;
    printf("Venda registrada com sucesso! ID da venda: %d\n", v.id_venda);
    return 1;
}

void mostrar_clientes() {
    printf("\n--- Lista de Clientes ---\n");
    for(int i=0; i<total_clientes; i++) {
        printf("Codigo: %d | Nome: %s | CPF: %s | Idade: %d\n",
            clientes[i].codigo, clientes[i].nome, clientes[i].cpf, clientes[i].idade);
    }
}

void mostrar_produtos() {
    printf("\n--- Lista de Produtos ---\n");
    for(int i=0; i<total_produtos; i++) {
        printf("Codigo: %d | %s - R$ %.2f\n",
            produtos[i].codigo, produtos[i].nome, produtos[i].preco);
    }
}

void listar_vendas() {
    printf("\n--- Vendas Realizadas ---\n");
    for(int i=0; i<total_vendas; i++) {
        printf("\nVenda ID: %d\nCliente ID: %d\n", vendas[i].id_venda, vendas[i].id_cliente);
        printf("Itens:\n");
        for(int j=0; j<vendas[i].total_itens; j++) {
            for(int k=0; k<total_produtos; k++) {
                if(produtos[k].codigo == vendas[i].itens[j]) {
                    printf("- %s x%d (R$ %.2f)\n",
                        produtos[k].nome, vendas[i].qtds[j], produtos[k].preco);
                }
            }
        }
        printf("Total: R$ %.2f\n", vendas[i].valor_final);
    }
}

void remover_cliente() {
    int id;
    mostrar_clientes();
    printf("Codigo do cliente a remover: ");
    scanf("%d", &id);

    for(int i=0; i<total_clientes; i++) {
        if(clientes[i].codigo == id) {
            for(int j=i; j<total_clientes-1; j++) {
                clientes[j] = clientes[j+1];
            }
            total_clientes--;
            printf("Cliente removido.\n");
            return;
        }
    }
    printf("Cliente nao encontrado.\n");
}

void remover_produto() {
    int id;
    mostrar_produtos();
    printf("Codigo do produto a remover: ");
    scanf("%d", &id);

    for(int i=0; i<total_produtos; i++) {
        if(produtos[i].codigo == id) {
            for(int j=i; j<total_produtos-1; j++) {
                produtos[j] = produtos[j+1];
            }
            total_produtos--;
            printf("Produto removido.\n");
            return;
        }
    }
    printf("Produto nao encontrado.\n");
}

void atualizar_cliente() {
    int id, opcao;
    mostrar_clientes();
    printf("Codigo do cliente a editar: ");
    scanf("%d", &id);

    for(int i=0; i<total_clientes; i++) {
        if(clientes[i].codigo == id) {
            printf("1-Nome 2-Idade 3-CPF 4-Cancelar: ");
            scanf("%d", &opcao);
            switch(opcao) {
                case 1:
                    printf("Novo nome: ");
                    scanf("%s", clientes[i].nome);
                    break;
                case 2:
                    printf("Nova idade: ");
                    scanf("%d", &clientes[i].idade);
                    break;
                case 3:
                    printf("Novo CPF: ");
                    scanf("%s", clientes[i].cpf);
                    break;
                case 4:
                    printf("Edicao cancelada.\n");
                    return;
                default:
                    printf("Opcao invalida.\n");
                    return;
            }
            printf("Cliente atualizado.\n");
            return;
        }
    }
    printf("Cliente nao encontrado.\n");
}

void atualizar_produto() {
    int id, opcao;
    mostrar_produtos();
    printf("Codigo do produto a editar: ");
    scanf("%d", &id);

    for(int i=0; i<total_produtos; i++) {
        if(produtos[i].codigo == id) {
            printf("1-Nome 2-Preco 3-Cancelar: ");
            scanf("%d", &opcao);
            switch(opcao) {
                case 1:
                    printf("Novo nome: ");
                    scanf("%s", produtos[i].nome);
                    break;
                case 2:
                    printf("Novo preco: ");
                    scanf("%f", &produtos[i].preco);
                    break;
                case 3:
                    printf("Edicao cancelada.\n");
                    return;
                default:
                    printf("Opcao invalida.\n");
                    return;
            }
            printf("Produto atualizado.\n");
            return;
        }
    }
    printf("Produto nao encontrado.\n");
}

void produto_top_vendas() {
    if(total_produtos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    int mais_vendido = -1;
    int indice = -1;
    for(int i=0; i<total_produtos; i++) {
        if(produtos[i].quantidade_vendida > mais_vendido) {
            mais_vendido = produtos[i].quantidade_vendida;
            indice = i;
        }
    }

    if(mais_vendido == 0) {
        printf("Nenhum produto foi vendido ainda.\n");
    } else {
        printf("Produto mais vendido:\n");
        printf("Codigo: %d\nNome: %s\nVendidos: %d\n",
            produtos[indice].codigo, produtos[indice].nome, produtos[indice].quantidade_vendida);
    }
}
