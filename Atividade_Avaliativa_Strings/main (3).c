#include <stdio.h>
#include <string.h>
#include "exercicios.h"

int main() {
    printf("--- INICIANDO VALIDACAO DOS PROTOTIPOS ---\n");

    // Teste 1: Contagem
    if(contar_palavras("Um, dois; tres") == 3) printf("Ex 01: [OK]\n");

    // Teste 2: Usuario
    char u[50];
    extrair_usuario("aluno@fatec.br", u);
    if(strcmp(u, "aluno") == 0) printf("Ex 02: [OK]\n");

    // Teste 5: Espaços
    char s5[50] = "A  B   C";
    enxugar_espacos(s5);
    if(strcmp(s5, "A B C") == 0) printf("Ex 05: [OK]\n");

    // Teste 10: Senha
    if(senha_forte("Senha123") == 1 && senha_forte("123") == 0) printf("Ex 10: [OK]\n");

    printf("\n--- TESTES CONCLUIDOS ---\n");
    return 0;
}
