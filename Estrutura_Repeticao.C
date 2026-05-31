#include <stdio.h>
#include <stdbool.h>
#include <math.h>




// Para compilar: gcc -Wall -Wextra exercicios.c -o testes -lm
// Para executar (Linux): ./textes
// ============================================================
// ESPAÇO PARA O ALUNO: IMPLEMENTAÇÕES
// ============================================================


// Implemente: soma_impares, verificar_potencia_dois, conta_divisores, 
// eh_primo, potencia, fibonacci, soma_digitos, media_multiplos_cinco, 
// inverte_numero, contagem_regressiva.

int soma_impares (int n) {
    if (n < 1){
        return 0;
    }

    int soma = 0;

    for (int i = 1; i <= n; i++){
        if (i % 2 != 0){
            soma += i;
        }
    }
    return soma;
}


int verificar_potencia_dois(int n){
    if (n < 1){
        return 0;
    }
    while (n > 1 ) {
        if (n % 2 != 0){
            return 0;
        }
        n = n / 2;
    }
    return 1;
}

int conta_divisores(int n){
    if (n <= 0){
        return 0;
    }
    int conta = 0;
    for (int i = 1; i <= n; i++){
        if (n % i == 0){
            conta++;
        }
    }
    return conta;
}


int eh_primo (int n){
    if (n <= 1){
        return 0;
    }
      for (int i = 2; i * i <= n; i++){
        if (n % i == 0){
            return 0;
        }
    }
    return 1;
}


int potencia(int base, int expoente){
    if (expoente == 0){
        return 1;
    }

    int resultado = 1;

    for (int i = 0; i < expoente; i++){
        resultado = resultado * base;
    }

    return resultado;
}

int fibonacci (int n){
    if (n <= 0){
        return 0;
    }
    if (n == 1 || n == 2){
        return 1;
    }
    int a = 1, b = 1, proximo;

    for (int i = 3; i <= n; i ++){
        proximo = a + b;
        a = b;
        b = proximo;
    }
    return b;
}

int soma_digitos (int n){
    int soma = 0;
    if (n < 0) n = -n;
    while (n > 0){
        soma += n % 10;
        n = n / 10;
    }
    return soma;
}

float media_multiplos_cinco(int inicio, int fim) {
    int soma = 0;
    int contador = 0;

    for (int i = inicio; i <= fim; i++) {
        if (i % 5 == 0) {
            soma += i;
            contador++;
        }
    }

    if (contador == 0) {
        return 0;
    }

    return (float)soma / contador;
}

int inverte_numero(int n) {
    int invertido = 0;
    int sinal = 1;

    if (n < 0) {
        sinal = -1;
        n = -n;
    }

    while (n > 0) {
        invertido = invertido * 10 + n % 10;
        n = n / 10;
    }

    return invertido * sinal;
}

int contagem_regressiva(int n) {
    if (n < 0) {
        return 0;
    }

    for (int i = n; i >= 0; i--) {
        printf("%d ", i);
    }
    printf("\n");

    return n + 1;
}

// ============================================================
// FIM DO ESPAÇO PARA O ALUNO
// ============================================================


void testar_int(const char* nome, int obtido, int esperado, const char* entradas) {
    if (obtido == esperado) {
        printf("[ OK ] %-20s\n", nome);
    } else {
        printf("[FAIL] %-20s | Entradas: %s\n", nome, entradas);
        printf("       -> Esperado: %d | Obtido: %d\n", esperado, obtido);
    }
}


void testar_float(const char* nome, float obtido, float esperado, const char* entradas) {
    if (fabsf(obtido - esperado) < 0.001f) {
        printf("[ OK ] %-20s\n", nome);
    } else {
        printf("[FAIL] %-20s | Entradas: %s\n", nome, entradas);
        printf("       -> Esperado: %.2f | Obtido: %.2f\n", esperado, obtido);
    }
}


int main() {
    printf("====================================================\n");
    printf("     RELATORIO DE AVALIACAO: REPETICAO (LOOPS)      \n");
    printf("====================================================\n");


    // Testes atualizados
    testar_int("1. soma_impares", soma_impares(10), 25, "n=10 (1+3+5+7+9)");
    testar_int("2. pot_dois", verificar_potencia_dois(16), 1, "n=16");
    testar_int("3. divisores", conta_divisores(12), 6, "n=12");
    testar_int("4. eh_primo", eh_primo(11), 1, "n=11");
    testar_int("5. potencia", potencia(3, 4), 81, "3^4");
    testar_int("6. fibonacci", fibonacci(7), 8, "n=7");
    testar_int("7. soma_digitos", soma_digitos(456), 15, "n=456");
    testar_float("8. media_mult_5", media_multiplos_cinco(10, 20), 15.0, "10 a 20");
    testar_int("9. inverte_num", inverte_numero(987), 789, "n=987");
    testar_int("10. cont_regress", contagem_regressiva(3), 4, "n=3 (3,2,1,0)");


    printf("====================================================\n");
    return 0;
}
