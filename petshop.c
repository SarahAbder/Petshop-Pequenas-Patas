#include <stdio.h>
#include <string.h>

#define MAX_TEXTO 50
#define MAX_ITENS 100
#define MAX_TENTATIVAS 3
#define USUARIO_CORRETO "admin"
#define SENHA_CORRETA "1234"

typedef struct {
    char nome[MAX_TEXTO];
    char telefone[MAX_TEXTO];
} Cliente;

typedef struct {
    char nome[MAX_TEXTO];
    int especie;
    char raca[MAX_TEXTO];
    int porte;
} Pet;

Cliente cliente;
Pet pet;
int clienteCadastrado = 0;
int petCadastrado = 0;
char funcionario[MAX_TEXTO];

/* vetores do comprovante (etapa 6) */
char descricoes[MAX_ITENS][MAX_TEXTO];
int quantidades[MAX_ITENS];
float valores[MAX_ITENS];
int totalItens = 0;

/* vetores dos produtos (etapa 5) */
const char *nomesAlimentos[3] = {"Racao cao 15kg", "Racao gato 5kg", "Bifinho"};
float precosAlimentos[3] = {150.00f, 89.90f, 12.50f};

const char *nomesAcessorios[3] = {"Coleira", "Bolinha", "Caminha"};
float precosAcessorios[3] = {25.00f, 12.00f, 80.00f};

const char *nomesHigiene[3] = {"Shampoo", "Escova", "Tapete higienico"};
float precosHigiene[3] = {30.00f, 20.00f, 45.00f};

/* ===================== FUNCOES AUXILIARES ===================== */

void lerTexto(const char *msg, char *destino, int tamanho) {
    printf("%s", msg);
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = '\0';
}

int lerInteiro(const char *msg) {
    char linha[20];
    int valor = -1;
    printf("%s", msg);
    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%d", &valor);
    return valor;
}

const char *nomeEspecie(int especie) {
    if (especie == 1) return "Cao";
    return "Gato";
}

const char *nomePorte(int porte) {
    switch (porte) {
        case 1: return "Pequeno";
        case 2: return "Medio";
        default: return "Grande";
    }
}

/* guarda o item nos vetores do comprovante */
int registrarItem(const char *descricao, int quantidade, float valor) {
    if (totalItens >= MAX_ITENS) {
        printf("Limite de itens atingido!\n");
        return 0;
    }
    snprintf(descricoes[totalItens], MAX_TEXTO, "%s", descricao);
    quantidades[totalItens] = quantidade;
    valores[totalItens] = valor;
    totalItens++;
    return 1;
}

/* ===================== ETAPA 1 - LOGIN ===================== */

int login(void) {
    char usuario[MAX_TEXTO];
    char senha[MAX_TEXTO];
    int tentativas;

    for (tentativas = 1; tentativas <= MAX_TENTATIVAS; tentativas++) {
        printf("\n===== LOGIN DO FUNCIONARIO =====\n");
        lerTexto("Usuario: ", usuario, MAX_TEXTO);
        lerTexto("Senha: ", senha, MAX_TEXTO);

        if (strcmp(usuario, USUARIO_CORRETO) == 0 && strcmp(senha, SENHA_CORRETA) == 0) {
            strcpy(funcionario, usuario);
            printf("\nLogin realizado com sucesso! Bem-vindo(a), %s.\n", funcionario);
            return 1;
        }

        printf("Usuario ou senha incorretos. Tentativas restantes: %d\n",
               MAX_TENTATIVAS - tentativas);
    }

    printf("\nNumero maximo de tentativas atingido. Encerrando o programa.\n");
    return 0;
}

/* ===================== ETAPA 3 - CADASTROS ===================== */

void cadastrarCliente() {
    printf("\n--- CADASTRAR CLIENTE ---\n");
    lerTexto("Nome: ", cliente.nome, MAX_TEXTO);
    lerTexto("Telefone: ", cliente.telefone, MAX_TEXTO);
    clienteCadastrado = 1;
    printf("Cliente cadastrado com sucesso!\n");
}

void cadastrarPet() {
    if (!clienteCadastrado) {
        printf("\nCadastre o cliente antes de cadastrar o pet.\n");
        return;
    }
    printf("\n--- CADASTRAR PET ---\n");
    lerTexto("Nome do pet: ", pet.nome, MAX_TEXTO);
    do {
        pet.especie = lerInteiro("Especie (1 - Cao, 2 - Gato): ");
        if (pet.especie != 1 && pet.especie != 2) {
            printf("Opcao invalida!\n");
        }
    } while (pet.especie != 1 && pet.especie != 2);
    lerTexto("Raca: ", pet.raca, MAX_TEXTO);
    do {
        pet.porte = lerInteiro("Porte (1 - Pequeno, 2 - Medio, 3 - Grande): ");
        if (pet.porte < 1 || pet.porte > 3) {
            printf("Opcao invalida!\n");
        }
    } while (pet.porte < 1 || pet.porte > 3);
    petCadastrado = 1;
    printf("Pet cadastrado com sucesso!\n");
}

void menuCadastros() {
    int opcao;

    do {
        printf("\n--------- CADASTROS ----------\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Cadastrar pet\n");
        printf("0 - Voltar\n");
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                cadastrarPet();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

/* ===================== ETAPA 4 - SERVICOS ===================== */

/* Banho: preco conforme o porte do pet (1-Pequeno, 2-Medio, 3-Grande) */
float banho(int porte) {
    switch (porte) {
        case 1: return 40.00f;
        case 2: return 60.00f;
        case 3: return 80.00f;
        default: return 0.0f;
    }
}

/* Tosa: preco conforme o tipo (1-Higienica, 2-Completa, 3-Na tesoura) */
float tosa(int tipo) {
    switch (tipo) {
        case 1: return 35.00f;
        case 2: return 70.00f;
        case 3: return 90.00f;
        default: return 0.0f;
    }
}

/* Veterinaria: 1-Consulta, 2-Vacina, 3-Exame */
float veterinaria(int opcao) {
    switch (opcao) {
        case 1: return 120.00f;
        case 2: return 80.00f;
        case 3: return 150.00f;
        default: return 0.0f;
    }
}

void servicoBanho() {
    char descricao[MAX_TEXTO];
    float valor = banho(pet.porte);

    snprintf(descricao, MAX_TEXTO, "Banho (porte %s)", nomePorte(pet.porte));
    if (registrarItem(descricao, 1, valor)) {
        printf("%s: R$ %.2f\n", descricao, valor);
    }
}

void servicoTosa() {
    int tipo;
    float valor;
    const char *nomes[3] = {"Tosa higienica", "Tosa completa", "Tosa na tesoura"};

    printf("Tipo de tosa:\n");
    printf("1 - Higienica (R$ 35.00)\n");
    printf("2 - Completa (R$ 70.00)\n");
    printf("3 - Na tesoura (R$ 90.00)\n");
    tipo = lerInteiro("Escolha: ");

    valor = tosa(tipo);
    if (valor == 0.0f) {
        printf("Opcao invalida!\n");
    } else if (registrarItem(nomes[tipo - 1], 1, valor)) {
        printf("%s: R$ %.2f\n", nomes[tipo - 1], valor);
    }
}

void servicoVeterinaria() {
    int opcao;
    float valor;
    const char *nomes[3] = {"Veterinaria - Consulta", "Veterinaria - Vacina", "Veterinaria - Exame"};

    printf("Servico veterinario:\n");
    printf("1 - Consulta (R$ 120.00)\n");
    printf("2 - Vacina (R$ 80.00)\n");
    printf("3 - Exame (R$ 150.00)\n");
    opcao = lerInteiro("Escolha: ");

    valor = veterinaria(opcao);
    if (valor == 0.0f) {
        printf("Opcao invalida!\n");
    } else if (registrarItem(nomes[opcao - 1], 1, valor)) {
        printf("%s: R$ %.2f\n", nomes[opcao - 1], valor);
    }
}

void menuServicos() {
    int opcao;

    /* servico so depois do cliente e do pet */
    if (!clienteCadastrado || !petCadastrado) {
        printf("\nCadastre o cliente e o pet antes de usar os servicos.\n");
        return;
    }

    do {
        printf("\n---------- SERVICOS ----------\n");
        printf("1 - Banho\n");
        printf("2 - Tosa\n");
        printf("3 - Veterinaria\n");
        printf("0 - Voltar\n");
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                servicoBanho();
                break;
            case 2:
                servicoTosa();
                break;
            case 3:
                servicoVeterinaria();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

/* ===================== ETAPA 5 - PRODUTOS ===================== */

void menuCategoria(const char *titulo, const char *nomes[], float precos[], int qtdProdutos) {
    int opcao, quantidade, i;
    float valor;

    do {
        printf("\n---------- %s ----------\n", titulo);
        for (i = 0; i < qtdProdutos; i++) {
            printf("%d - %-18s R$ %7.2f\n", i + 1, nomes[i], precos[i]);
        }
        printf("0 - Voltar\n");
        opcao = lerInteiro("Escolha o produto: ");

        if (opcao == 0) {
            break;
        }
        if (opcao < 1 || opcao > qtdProdutos) {
            printf("Opcao invalida! Tente novamente.\n");
        } else {
            quantidade = lerInteiro("Quantidade: ");
            if (quantidade <= 0) {
                printf("Quantidade invalida!\n");
            } else {
                valor = precos[opcao - 1] * quantidade;
                if (registrarItem(nomes[opcao - 1], quantidade, valor)) {
                    printf("Produto: %s   Quantidade: %d   Valor: R$ %.2f\n",
                           nomes[opcao - 1], quantidade, valor);
                }
            }
        }
    } while (opcao != 0);
}

void menuProdutos() {
    int opcao;

    do {
        printf("\n---------- PRODUTOS ----------\n");
        printf("1 - Alimentos\n");
        printf("2 - Acessorios\n");
        printf("3 - Higiene\n");
        printf("0 - Voltar\n");
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                menuCategoria("ALIMENTOS", nomesAlimentos, precosAlimentos, 3);
                break;
            case 2:
                menuCategoria("ACESSORIOS", nomesAcessorios, precosAcessorios, 3);
                break;
            case 3:
                menuCategoria("HIGIENE", nomesHigiene, precosHigiene, 3);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

/* ===================== ETAPA 6 - COMPROVANTE FINAL ===================== */

void comprovanteFinal() {
    int i;
    float total = 0.0f;

    if (!clienteCadastrado || !petCadastrado) {
        printf("\nCadastre o cliente e o pet antes de emitir o comprovante.\n");
        return;
    }

    printf("\n==============================\n");
    printf("      COMPROVANTE FINAL\n");
    printf("==============================\n");
    printf("Funcionario: %s\n", funcionario);
    printf("Cliente: %s (Tel: %s)\n", cliente.nome, cliente.telefone);
    printf("Pet: %s - %s - %s - Porte %s\n", pet.nome, nomeEspecie(pet.especie),
           pet.raca, nomePorte(pet.porte));
    printf("------------------------------\n");

    if (totalItens == 0) {
        printf("Nenhum item registrado.\n");
    }
    for (i = 0; i < totalItens; i++) {
        printf("%d - %-24s Qtd: %d   R$ %.2f\n", i + 1, descricoes[i], quantidades[i], valores[i]);
        total += valores[i];
    }

    printf("------------------------------\n");
    printf("TOTAL DO ATENDIMENTO: R$ %.2f\n", total);
    printf("==============================\n");
}

/* ===================== MENU PRINCIPAL ===================== */

void menuPrincipal() {
    int opcao;

    do {
        printf("\n==============================\n");
        printf("    PETSHOP PEQUENAS PATAS\n");
        printf("==============================\n");
        printf("1 - Cadastros\n");
        printf("2 - Servicos\n");
        printf("3 - Produtos\n");
        printf("4 - Comprovante final\n");
        printf("0 - Sair\n");
        printf("==============================\n");
        opcao = lerInteiro("Escolha uma opcao: ");

        switch (opcao) {
            case 1:
                menuCadastros();
                break;
            case 2:
                menuServicos();
                break;
            case 3:
                menuProdutos();
                break;
            case 4:
                comprovanteFinal();
                break;
            case 0:
                printf("\nEncerrando o sistema. Ate logo!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

int main() {
    if (!login()) {
        return 0;
    }
    menuPrincipal();
    return 0;
}