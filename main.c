//gcc main.c -o main && ./main

#include <stdio.h>
#include <stdlib.h>

#define MAX_PRODUTOS 200
#define MAX_CATEGORIAS 6

struct Produto {
    int codigo;
    char nome[100];
    int categoria;
    int quantDisponivel;
    int quantMinima;
    float valorUnitario;
    int situacao;
};

//Cabeçalho das funções do sistema {

//Funções de menu do sistema:
void exibirMenu(void);
void exibirMenuRelatorios(void);
void menuRelatorios(void);

//Funções de cadastro, alteração e exclusão:
void cadastrarProduto();
void alterarProduto();
void excluirProduto();
void codigoExiste();
void buscarIndicePorCodigo();

//Funções de entrada/saída:
void registrarEntrada();
void registrarSaida();

//Funções de consulta do sistema:
void consultarPorCodigo();
void consultarPorNome();
void consultarPorCategoria();
void listarTodos();
void listarAbaixoDoMinimo();
void listarSemEstoque();
void listarIndisponiveis();

//Funções de pesistência de dados:
void salvarDados();
void carregarDados();

//Funções de relatórios do sistema:
void relatorioGeral();
void relatorioAbaixoDoMinimo();
void relatorioSemEstoque();
void relatorioPorNome();
void relatorioPorQuantidade();
void relatorioPorValor();
void relatorioValorPorProduto();
void relatorioValorTotalEstoque();
void relatorioMaiorValorUnitario();
void relatorioMaiorValorArmazenado();
void relatorioPorCategoria();

//Funções de validação do sistema:
int validarNome(char nome[]);
int validarValorUnitario(float valorUnitario);
int validarCategoria(int categoria);
int validarQuantidadeMinima(int quantMinima);
int validarQuantidadeInicial(int quantDisponivel);
int validarExclusao(int quantDisponivel);
int validarLimiteProdutos(int total);
int validarQuantidadeOperacao(int quantDisponivel);
int validarEstoqueSuficiente(int quantDisponivel, int quantSaida);

// }

int main(void) {
    struct Produto estoque[MAX_PRODUTOS];
    int total = 0;
    int opcao = 0;

    //carregarDados();

    while (opcao != 16) {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                cadastrarProduto();
                break;

            case 2:
                consultarPorCodigo();
                break;

            case 3:
                consultarPorNome();
                break;

            case 4:
                consultarPorCategoria();
                break;

            case 5:
                listarTodos();
                break;

            case 6:
                alterarProduto();
                break;

            case 7:
                excluirProduto();
                break;

            case 8:
                registrarEntrada();
                break;

            case 9:
                registrarSaida();
                break;

            case 10:
                listarAbaixoDoMinimo();
                break;

            case 11:
                listarSemEstoque();
                break;

            case 12:
                listarIndisponiveis();
                break;

            case 13:
                menuRelatorios();
                break;

            case 14:
                salvarDados();
                break;

            case 15:
                carregarDados();
                break;

            case 16:
                salvarDados();
                return 0;

            default:
                printf("Insira uma opção entre 1 e 16!\n");
                break;
        }
    }


    return 0;
}

void exibirMenu(void) {
    printf("-=-=-=-=-=-= Controle de Estoque -=-=-=-=-=-=");
    printf("\n[1] Cadastrar produto");
    printf("\n[2] Consultar produto pelo código");
    printf("\n[3] Consultar produto pelo nome");
    printf("\n[4] Consultar produtos por categoria");
    printf("\n[5] Listar todos os produtos");
    printf("\n[6] Alterar dados de um produto");
    printf("\n[7] Excluir ou descontinuar um produto");
    printf("\n[8] Registrar entrada");
    printf("\n[9] Registrar saída");
    printf("\n[10] Consultar produtos com estoque abaixo do mínimo");
    printf("\n[11] Consultar produtos sem estoque");
    printf("\n[12] Consultar produtos temporariamente indisponíveis");
    printf("\n[13] Apresentar relatórios");
    printf("\n[14] Salvar as informações");
    printf("\n[15] Recuperar as informações armazenadas anteriormente");
    printf("\n[16] Encerrar o sistema\n");
    printf("\n");
}

void exibirMenuRelatorios(void) {
    printf("-=-=-=-=-=-= Relatorios -=-=-=-=-=-=\n");
    printf("[0] Voltar ao menu\n");
    printf("[1] Relatório geral\n");
    printf("[2] Relatório de produtos com estoque abaixo do mínimo\n");
    printf("[3] Relatório produto sem estoque\n");
    printf("[4] Relatório por nome\n");
    printf("[5] Relatório por quantidade\n");
    printf("[6] Relatorio por valor\n");
    printf("[7] Relatório por produto e valor\n");
    printf("[8] Valor total do estoque\n");
    printf("[9] Maior valor unitário\n");
    printf("[10] Maior valor armazenado\n");
    printf("[11] Relatório por categoria\n");
    printf("\n");
}

void menuRelatorios(void) {
    int opcao = 1;

    while (opcao != 0) {
        exibirMenuRelatorios();
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                break;

            case 1:
                relatorioGeral();
                break;
                
            case 2:
                relatorioAbaixoDoMinimo();
                break;

            case 3:
                relatorioSemEstoque();
                break;

            case 4:
                relatorioPorNome();
                break;

            case 5:
                relatorioPorQuantidade();
                break;

            case 6:
                relatorioPorValor();
                break;

            case 7:
                relatorioValorPorProduto();
                break;

            case 8:
                relatorioValorTotalEstoque();
                break;

            case 9:
                relatorioMaiorValorUnitario();
                break;

            case 10:
                relatorioMaiorValorArmazenado();
                break;

            case 11:
                relatorioPorCategoria();
                break;

            default:
                printf("Opção inválida");
                break;
        }
    }    
}

int validarNome(char nome[]) {
    if (nome[0] == '\0') {
        return 0;
    } 

    return 1;
}

int validarValorUnitario(float valorUnitario) {
    if (valorUnitario > 0) {
        return 1;
    }

    return 0;
}

int validarCategoria(int categoria) {
    if (categoria > 0 && categoria <= MAX_CATEGORIAS) {
        return 1;
    }

    return 0;
}

int validarQuantidadeMinima(int quantMinima) {
    if (quantMinima < 0) {
        return 0;
    }

    return 1;
}

int validarQuantidadeInicial(int quantDisponivel) {
    if (quantDisponivel < 0) {
        return 0;
    }

    return 1;
}

int validarExclusao(int quantDisponivel) {
    if (quantDisponivel == 0) {
        return 1;
    }

    return 0;
}

int validarLimiteProdutos(int total) {
    if (total >= MAX_PRODUTOS) {
        return 0;
    }

    return 1;
}

int validarQuantidadeOperacao(int quantDisponivel) {
    if (quantDisponivel > 0) {
        return 1;
    }
    return 0;
}

int validarEstoqueSuficiente(int quantDisponivel, int quantSaida) {
    if (quantSaida > quantDisponivel) {
        return 0;
    }

    return 1;
}

