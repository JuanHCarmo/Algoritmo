#include <stdio.h>
#include <stdbool.h>

int mdc_euclides(int a, int b){
    while (a != b){
        if (a > b) {
            a = a - b;
        } else {
            b = b - a;
        }
    }
    return a;
}

int mmc_repeticao(int a, int b){
    int m = (a > b) ? a : b;

    while (1){
        if (m % a == 0 && m % b == 0){
            return m;
        }
        m++;
    }
}

int decimal_para_binario(int n){
    int binario = 0;
    int multiplicador = 1;

    while (n > 0){
        int digito = n % 2;
        binario += digito * multiplicador;
        multiplicador *= 10;
        n = n / 2;
    }
    return binario;
}

void testar(const char* ex, int obtido, int esperado) {
    if (obtido == esperado)
        printf("[ OK ] %s\n", ex);
    else
        printf("[FAIL] %s | Esp: %d | Obt: %d\n", ex, esperado, obtido);
}

int main() {
    printf("--- TESTES ---\n");

    testar("MDC", mdc_euclides(48, 18), 6);
    testar("MMC", mmc_repeticao(4, 6), 12);
    testar("Binario", decimal_para_binario(13), 1101);

    return 0;
}