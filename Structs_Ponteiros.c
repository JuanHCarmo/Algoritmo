

Pular para o conteúdo
Como usar o E-mail de Universidade Tecnologica Federal do Paraná com leitores de tela
Ativar as notificações na área de trabalho para o E-mail de Universidade Tecnologica Federal do Paraná.
   OK  Agora não(a)

13 de 1.466
Atividade Structs e Ponteiros
Caixa de entrada

JUAN HENRIQUE DO CARMO <juanhenrique@alunos.utfpr.edu.br>
Anexos
ter., 26 de mai., 20:43 (há 5 dias)
para mim


 1 anexo
  •  Verificados pelo Gmail
#include <stdio.h>
#include <string.h>

#define QTD_CLIENTES 3

// ==========================================
// DEFINIÇÃO DA STRUCT
// ==========================================
typedef struct {
    int numero;
    char titular[50];
    float saldo;
} ContaBancaria;

// ==========================================
// PROTÓTIPOS DAS FUNÇÕES
// ==========================================
void exibirConta(ContaBancaria conta);
void exibirBanco(ContaBancaria vetor[], int tamanho);
void depositar(ContaBancaria *conta, float valor);
int sacar(ContaBancaria *conta, float valor);
ContaBancaria* encontrarConta(ContaBancaria vetor[], int tamanho, int numeroBusca);
int transferir(ContaBancaria *origem, ContaBancaria *destino, float valor);
float calcularPatrimonioTotal(ContaBancaria vetor[], int tamanho);

// ==========================================
// FUNÇÃO MAIN (NÃO ALTERAR)
// ==========================================
int main() {
    printf("=== SISTEMA DE MOVIMENTACAO BANCARIA ===\n\n");

    // Inicialização estática do vetor de clientes
    ContaBancaria meuBanco[QTD_CLIENTES] = {
        {100, "Andre Mendes", 1000.00},
        {200, "Alice Silva",    500.00},
        {300, "Bruno Santos",    50.00}
    };

    // 1. Situação Inicial do Banco
    printf("--- Estado Inicial do Banco ---\n");
    exibirBanco(meuBanco, QTD_CLIENTES);
    printf("Patrimonio Total do Banco: R$ %.2f\n\n", calcularPatrimonioTotal(meuBanco, QTD_CLIENTES));

    // 2. Teste de Busca e Depósito por Referência
    printf("--- Operacao: Deposito de R$ 250.00 na Conta 100 ---\n");
    ContaBancaria *contaEncontrada = encontrarConta(meuBanco, QTD_CLIENTES, 100);
    if (contaEncontrada != NULL) {
        depositar(contaEncontrada, 250.00); 
        printf("Deposito realizado com sucesso!\n");
        exibirConta(*contaEncontrada); 
    } else {
        printf("Conta nao encontrada.\n");
    }
    printf("\n");

    // 3. Teste de Saque (Com sucesso e com falha)
    printf("--- Operacao: Tentativa de Saques na Conta 300 ---\n");
    contaEncontrada = encontrarConta(meuBanco, QTD_CLIENTES, 300);
    if (contaEncontrada != NULL) {
        printf("Tentando sacar R$ 100.00...\n");
        if (sacar(contaEncontrada, 100.00)) {
            printf("Saque realizado!\n");
        } else {
            printf("Falha: Saldo insuficiente. (Saldo atual: R$ %.2f)\n", contaEncontrada->saldo);
        }

        printf("Tentando sacar R$ 30.00...\n");
        if (sacar(contaEncontrada, 30.00)) {
            printf("Saque realizado com sucesso!\n");
            exibirConta(*contaEncontrada);
        }
    }
    printf("\n");

    // 4. Teste de Transferência entre Clientes distintos
    printf("--- Operacao: Transferencia de R$ 200.00 da Conta 100 para Conta 200 ---\n");
    ContaBancaria *contaOrigem  = encontrarConta(meuBanco, QTD_CLIENTES, 100);
    ContaBancaria *contaDestino = encontrarConta(meuBanco, QTD_CLIENTES, 200);

    if (contaOrigem != NULL && contaDestino != NULL) {
        printf("Antes da transferencia:\n");
        exibirConta(*contaOrigem);
        exibirConta(*contaDestino);

        if (transferir(contaOrigem, contaDestino, 200.00)) {
            printf("\nTransferencia concluida com sucesso!\n");
            printf("Depois da transferencia:\n");
            exibirConta(*contaOrigem);
            exibirConta(*contaDestino);
        } else {
            printf("\nFalha na transferencia: Saldo insuficiente na conta de origem.\n");
        }
    }
    printf("\n");

    // 5. Testes de Borda (Edge Cases)
    printf("--- Testes de Verificacao de Ponteiros Nulos ---\n");
    ContaBancaria *contaFantasma = encontrarConta(meuBanco, QTD_CLIENTES, 999);
    if (contaFantasma == NULL) {
        printf("Sucesso no teste: Sistema tratou corretamente busca de conta inexistente.\n");
    } else {
        printf("ERRO: O sistema retornou um ponteiro valido para uma conta inexistente!\n");
    }
    printf("\n");

    // 6. Situação Final do Banco
    printf("--- Estado Final do Banco ---\n");
    exibirBanco(meuBanco, QTD_CLIENTES);
    printf("Patrimonio Total Final do Banco: R$ %.2f\n", calcularPatrimonioTotal(meuBanco, QTD_CLIENTES));

    return 0;
}

// ==========================================
// IMPLEMENTE AS FUNCOES ABAIXO DESTE PONTO
// ==========================================


void exibirConta(ContaBancaria conta){
    printf("Conta: %d, Titular: %s, aldo: %.2f", conta.numero, conta.titular, conta.saldo);
}
Ponteiros.c
Exibindo Ponteiros.c.