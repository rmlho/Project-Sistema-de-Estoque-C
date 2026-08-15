//gcc main.c -o main && ./main

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 200
#define MAX_CATEGORIAS 6
#define MAX_CODIGO 999

struct Produto {
    int codigo;
    char nome[100];
    int categoria;
    int quantDisponivel;
    int quantMinima;
    float valorUnitario;
    int situacao;
};

/* NOTA: codigo usa 4 digitos inteiros
categoria de 1 a 6  
 1. Materia de escritório
 2. Material de limpeza
 3. Equipamentos
 4. Componentes eletrônicos
 5. Ferramentas
 6. Acessórios

e a situacao tambem em inteiros 

 1. ATIVO
 2. INDISPONIVEL
 3. DESCONTINUADO
*/

//Cabeçalho das funções do sistema {

//Funções de menu do sistema:
void exibirMenu(void);
void exibirMenuRelatorios(void);
void menuRelatorios(void);

//Funções de cadastro, alteração e exclusão:
void cadastrarProduto(struct Produto estoque[], int *total);
void alterarProduto(struct Produto estoque[], int total);
void excluirProduto(struct Produto estoque[], int *total);
void codigoExiste(struct Produto estoque[], int total);
int buscarIndicePorCodigo(struct Produto estoque[], int total, int codigo);

//Funções de entrada/saída:
void registrarEntrada(struct Produto estoque[], int total);
void registrarSaida();

//Funções de consulta do sistema:
void consultarPorCodigo();
void consultarPorNome();
void consultarPorCategoria();
void consultarPorSituacao();
void listarTodos(struct Produto estoque[], int total);
void listarAbaixoDoMinimo(struct Produto estoque[], int total);
void listarSemEstoque(struct Produto estoque[], int total);
void listarIndisponiveis(struct Produto estoque[], int total);

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
int validarCodigo(int codigo);
int validarProdutoAtivo(int situacao);
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

    carregarDados();

    while (opcao != 16) {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                cadastrarProduto(estoque, &total);
                break;

            case 2:
                consultarPorCodigo(estoque, total);
                break;

            case 3:
                consultarPorNome();
                break;

            case 4:
                consultarPorCategoria();
                break;

            case 5:
                listarTodos(estoque, total);
                break;

            case 6:
                alterarProduto(estoque, total);
                break;

            case 7:
                excluirProduto(estoque, &total);
                break;

            case 8:
                registrarEntrada(estoque, total);
                break;

            case 9:
                registrarSaida();
                break;

            case 10:
                listarAbaixoDoMinimo(estoque, total);
                break;

            case 11:
                listarSemEstoque(estoque, total);
                break;

            case 12:
                listarIndisponiveis(estoque, total);
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

int validarCodigo(int codigo) {
    if (codigo < 1000 && codigo > MAX_CODIGO) {
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

int validarProdutoAtivo(int situacao) {
    if (situacao == 1) {
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

void cadastrarProduto(struct Produto estoque[], int *total) {

    if (!validarLimiteProdutos(*total)) {
        printf("Erro: limite de %d produtos atingido!\n", MAX_PRODUTOS);
        return;
    }

    int codigo;
    char nome[100];
    int categoria;
    int quantDisponivel;
    int quantMinima;
    float valorUnitario;
    
    printf("--- CADASTRO DE PRODUTO ---\n");
    printf("Categorias: 1. Material de escritorio; 2. Material de limpeza; 3. Equipamentos; 4. Componentes eletrônicos; 5. Ferramentas; 6. Acessórios\n");
    printf("\n");

    printf("Codigo de 4 digitos: ");
    scanf("%d", &codigo);

    if (!validarCodigo(codigo)) {
        printf("Erro: coódigo deve ter 4 digitos!\n");
        return;
    } 

    if (buscarIndicePorCodigo(estoque, *total, codigo) != -1) {
        printf("Erro: codigo ja cadastrado!\n");
        return;
    }

    printf("Nome: ");
    scanf(" %99[^\n]", nome);

    if (!validarNome(nome)) {
        printf("Erro: nome nao pode ser vazio!\n");
        return;
    }

    printf("Categoria (codigo numerico): ");
    scanf("%d", &categoria);

    if (!validarCategoria(categoria)) {
        printf("Erro: categoria invalida!\n");
        return;
    }

    printf("Quantidade inicial: ");
    scanf("%d", &quantDisponivel);

    if (!validarQuantidadeInicial(quantDisponivel)) {
        printf("Erro: quantidade inicial nao pode ser negativa!\n");
        return;
    }

    printf("Quantidade minima: ");
    scanf("%d", &quantMinima);

    if (!validarQuantidadeMinima(quantMinima)) {
        printf("Erro: quantidade minima nao pode ser negativa!\n");
        return;
    }

    printf("Valor unitario: ");
    scanf("%f", &valorUnitario);

    if (!validarValorUnitario(valorUnitario)) {
        printf("Erro: valor unitario deve ser maior que zero!\n");
        return;
    }

    estoque[*total].codigo = codigo;
    strcpy(estoque[*total].nome, nome);
    estoque[*total].categoria = categoria;
    estoque[*total].quantDisponivel = quantDisponivel;
    estoque[*total].quantMinima = quantMinima;
    estoque[*total].valorUnitario = valorUnitario;
    estoque[*total].situacao = 1; // 1 = ativo

    (*total)++;

    printf("\nProduto cadastrado com sucesso!\n\n");
}

int buscarIndicePorCodigo(struct Produto estoque[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (estoque[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void consultarPorCodigo(struct Produto estoque[], int total) {
    int codigo;
    printf("Digite o codigo do produto que deseja buscar:\n");
    scanf("%d", &codigo);

    int indice = buscarIndicePorCodigo(estoque, total, codigo);

    if (indice != -1) {
        printf("\n--- Produto Encontrado ---\n");
        printf("Codigo: %d\n", estoque[indice].codigo);
        printf("Nome: %s\n", estoque[indice].nome);
        printf("Categoria (Cod): %d\n", estoque[indice].categoria);
        printf("Qtd Disponivel: %d\n", estoque[indice].quantDisponivel);
        printf("Qtd Minima: %d\n", estoque[indice].quantMinima);
        printf("Valor Unitario: R$ %.2f\n", estoque[indice].valorUnitario);

        if (estoque[indice].situacao == 1) {
            printf("Situacao: Ativo\n");
        } else if (estoque[indice].situacao == 2) {
            printf("Situacao: Temporariamente Indisponivel\n");
        } else {
            printf("Situacao: Descontinuado\n");
        }
        printf("--------------------------\n\n");
    } else {
        printf("\nNenhum produto cadastrado com o codigo %d.\n\n", codigo);
    }
}

void alterarProduto(struct Produto estoque[], int total) {
    int codigo;

    printf("Digite o codigo do produto que deseja alterar:\n");
    scanf("%d", &codigo);

    int indice = buscarIndicePorCodigo(estoque, total, codigo);

    if (indice != -1) {
        printf("\n--- Dados Atuais do Produto ---\n");
        printf("Codigo: %d\n", estoque[indice].codigo);
        printf("Nome: %s\n", estoque[indice].nome);
        printf("Categoria (Cod): %d\n", estoque[indice].categoria);
        printf("Qtd Disponivel: %d\n", estoque[indice].quantDisponivel);
        printf("Qtd Minima: %d\n", estoque[indice].quantMinima);
        printf("Valor Unitario: R$ %.2f\n", estoque[indice].valorUnitario);
        printf("Situacao: %d\n", estoque[indice].situacao);
        printf("-------------------------------\n\n");

        char confirmacao;
        printf("Deseja realmente alterar os dados deste produto? (s/n): ");
        scanf(" %c", &confirmacao);

        if (confirmacao == 's' || confirmacao == 'S') {

            char novoNome[100];
            printf("\nDigite o novo nome do produto: ");
            scanf(" %99[^\n]", novoNome);
            if (!validarNome(novoNome)) {
                printf("Erro: nome nao pode ser vazio! Alteracao cancelada.\n");
                return;
            }

            int novaCategoria;
            printf("Informe a nova categoria (Codigo numerico): ");
            scanf("%d", &novaCategoria);
            if (!validarCategoria(novaCategoria)) {
                printf("Erro: categoria invalida! Alteracao cancelada.\n");
                return;
            }

            int novaQuantMinima;
            printf("Informe a nova quantidade minima recomendada: ");
            scanf("%d", &novaQuantMinima);
            if (!validarQuantidadeMinima(novaQuantMinima)) {
                printf("Erro: quantidade minima nao pode ser negativa! Alteracao cancelada.\n");
                return;
            }

            float novoValor;
            printf("Informe o novo valor unitario: R$ ");
            scanf("%f", &novoValor);
            if (!validarValorUnitario(novoValor)) {
                printf("Erro: valor unitario deve ser maior que zero! Alteracao cancelada.\n");
                return;
            }

            int novaSituacao;
            printf("Informe a nova situacao (1-Ativo, 2-Indisponivel, 3-Descontinuado): ");
            scanf("%d", &novaSituacao);
            if (novaSituacao < 1 || novaSituacao > 3) {
                printf("Erro: situacao invalida! Alteracao cancelada.\n");
                return;
            }

            strcpy(estoque[indice].nome, novoNome);
            estoque[indice].categoria = novaCategoria;
            estoque[indice].quantMinima = novaQuantMinima;
            estoque[indice].valorUnitario = novoValor;
            estoque[indice].situacao = novaSituacao;

            printf("\nProduto alterado com sucesso!\n");
        } else {
            printf("\nAlteracao cancelada.\n");
        }
    } else {
        printf("\nNenhum produto encontrado com o codigo %d.\n", codigo);
    }
}

void excluirProduto(struct Produto estoque[], int *total) {
    int codigo;

    printf("Digite o codigo do produto que deseja excluir:\n");
    scanf("%d", &codigo);

    int indice = buscarIndicePorCodigo(estoque, *total, codigo);

    if (indice != -1) {
        printf("\n--- Dados do Produto ---\n");
        printf("Codigo: %d\n", estoque[indice].codigo);
        printf("Nome: %s\n", estoque[indice].nome);
        printf("Qtd Disponivel: %d\n", estoque[indice].quantDisponivel);
        printf("------------------------\n\n");

        if (!validarExclusao(estoque[indice].quantDisponivel)) {
            printf("Erro: A exclusao nao pode ser realizada. Ainda existem %d unidades em estoque.\n", estoque[indice].quantDisponivel);
        } else {
            char confirmacao;

            printf("O produto possui 0 unidades em estoque. Deseja realmente exclui-lo definitivamente? (s/n): ");
            scanf(" %c", &confirmacao);

            if (confirmacao == 's' || confirmacao == 'S') {

                for (int i = indice; i < (*total) - 1; i++) {
                    estoque[i] = estoque[i + 1];
                }

                (*total)--;

                printf("\nProduto excluido definitivamente com sucesso!\n");
            } else {
                printf("\nExclusao cancelada.\n");
            }
        }
    } else {
        printf("\nNenhum produto encontrado com o codigo %d.\n", codigo);
    }
}

void listarTodos(struct Produto estoque[], int total) {
    int count = 0;
    int i;

    for (i = 0; i < total; i++) {
        printf("Código - %d\n", estoque[i].codigo);
        printf("Nome - %s\n", estoque[i].nome);
        printf("Categoria - %d\n", estoque[i].categoria);
        printf("Quantidade - %d\n", estoque[i].quantDisponivel);
        printf("Quantidade mínima - %d\n", estoque[i].quantMinima);
        printf("Valor unitario - %.2f\n", estoque[i].valorUnitario);
        printf("Situação - %d\n", estoque[i].situacao);
        puts("----------------------------------------\n");
        count++;
    }

    if (count == 0) {
        printf("Nenhum produto foi cadastrado\n");
    }
}

void listarAbaixoDoMinimo(struct Produto estoque[], int total) {
    int i;
    int count = 0;

    for (i = 0; i < total; i++) {
        if (estoque[i].quantDisponivel < estoque[i].quantMinima) {
            printf("Código - %d\n", estoque[i].codigo);
            printf("Nome - %s\n", estoque[i].nome);
            printf("Categoria - %d\n", estoque[i].categoria);
            printf("Quantidade - %d\n", estoque[i].quantDisponivel);
            printf("Quantidade mínima - %d\n", estoque[i].quantMinima);
            printf("Valor unitario - %.2f\n", estoque[i].valorUnitario);
            printf("Situação - %d\n", estoque[i].situacao);
            puts("----------------------------------------\n");
            count++;
        }
    }

     if (count == 0) {
        printf("Nenhum produto abaixo do mínimo\n");
    }    
}

void listarSemEstoque(struct Produto estoque[], int total) {
    int i;
    int count = 0;

    for (i = 0; i < total; i++) {
        if (estoque[i].quantDisponivel == 0) {
            printf("Código - %d\n", estoque[i].codigo);
            printf("Nome - %s\n", estoque[i].nome);
            printf("Categoria - %d\n", estoque[i].categoria);
            printf("Quantidade - %d\n", estoque[i].quantDisponivel);
            printf("Quantidade mínima - %d\n", estoque[i].quantMinima);
            printf("Valor unitario - %.2f\n", estoque[i].valorUnitario);
            printf("Situação - %d\n", estoque[i].situacao);
            puts("----------------------------------------\n");
            count++;
        }
    }

    if (count == 0) {
        printf("Nenhum produto sem estoque\n");
    }
}

void listarIndisponiveis(struct Produto estoque[], int total) {
    int i;
    int count = 0;

    for (i = 0; i < total; i++) {
        if (estoque[i].situacao == 2) {
            printf("Código - %d\n", estoque[i].codigo);
            printf("Nome - %s\n", estoque[i].nome);
            printf("Categoria - %d\n", estoque[i].categoria);
            printf("Quantidade - %d\n", estoque[i].quantDisponivel);
            printf("Quantidade mínima - %d\n", estoque[i].quantMinima);
            printf("Valor unitario - %.2f\n", estoque[i].valorUnitario);
            printf("Situação - %d\n", estoque[i].situacao);
            puts("----------------------------------------\n");
            count++;
        }
    }

    if (count == 0) {
        printf("Nenhum produto indisponivel\n");
    }
}

void registrarEntrada(struct Produto estoque[], int total) {
    int aux = 0;
    int quantRecebida;
    int indice;
    int codigo;

    printf("=-=-=-=-=-=- REGISTRANDO ENTRADA =-=-=-=-=-=-\n");
    printf("Informe o código do produto: \n");
    scanf("%d", &codigo);

    indice = buscarIndicePorCodigo(estoque ,total ,codigo);

    if (indice == -1) {
        printf("Produto não existe no estoque!\n");
        return;
    }

    if (!validarProdutoAtivo(estoque[indice].situacao)) {
        printf("Esse produto não está ativo!\n");
        return;
    }

    printf("Informe a quantidade recebida do produto: \n");
    scanf("%d", &quantRecebida);

    if (!validarQuantidadeOperacao(quantRecebida)) {
        printf("A quantidade DEVE ser maior que zero!\n");
        return;
    }

    aux = estoque[indice].quantDisponivel;
    estoque[indice].quantDisponivel += quantRecebida;

    printf("-------------------------------------------\n");
    printf("%s\n", estoque[indice].nome);
    printf("Quantidade anterior: %d\n", aux);
    printf("Quantidade recebida: %d\n", quantRecebida);
    printf("Nova quantidade disponivel: %d\n", estoque[indice].quantDisponivel);
}

