#include <stdio.h>


#include <stdbool.h>


#include <math.h>


// ============================================================


// ESPAÇO PARA O ALUNO: IMPLEMENTAÇÕES


// ============================================================


/* Implemente aqui: 


   1. eh_par, 2. esta_entre, 3. divisivel_por, 4. quantidade_dias_mes, 


   5. pontuacao, 6. desconto, 7. e_bissexto, 8. operacao_matematica, 


   9. tipo_caracter, 10. soma_maior_menor.


*/

int eh_par(int n){
    if  (n % 2  == 0) {
        return 1;
    } else {
        return 0;
    }

}

int esta_entre (int valor, int limite_inferior, int limite_superior){
    if (valor >= limite_inferior && valor <= limite_superior){
        return 1;
    } else {
        return 0;
    }

}

int divisivel_por (int a, int b){
    if (b == 0){
        return -1;
    }
    if (a % b == 0){
        return 1;
    } else {
        return 0;
    }
}

int quantidade_dias_mes(int mes ){
    if (mes < 1 || mes > 12){
        return -1;
    }
    if (mes == 2) {
        return 28;
    }
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        return 30;
    }
    return 31;
}

int pontuacao(int idade){
    if (idade < 18){
        return 100;
    }
    if (idade <= 60 ){
        return 200;
    }
    return 150;
}

float desconto(float valor, int categoria){
    if (categoria == 1 &&  valor > 100){
        return valor * 0.05;
    }
    if (categoria == 2 && valor > 200){
        return valor * 0.10;
    }
    return 0;
}  

int e_bissexto(int ano){
    if (ano % 400 == 0){
        return 1;
    }
    if (ano % 100 == 0){
        return 0;
    }
    if (ano % 4 == 0){
        return 1;
    }
    return 0;
}

float operacao_matematica(float x, float y, char op){
    if (op == '+'){
        return x + y;
    }
    if (op == '-'){
        return x - y;
    }
    if (op == '*'){
        return x * y;
    }
    if (op == '/'){
        if (y == 0){
            return 0;
        }
        return x / y;
    }
    
    return 0;
}

int tipo_caracter(char c){
    if ((c >= 'A'  &&  c <= 'Z') || (c >= 'a' && c <= 'z')){
        return 0;
    }
    if (c >= '0' && c <= '9'){
        return 1;
    }
    return 2;
}


int soma_maior_menor(int a, int b, int c){
    int maior = a;
    int menor = a;

    if (b > maior) maior = b;
    if (c > maior) maior = c;

    if (b < menor) menor = b;
    if (c < menor) menor = c;

    return maior + menor ;
}



// ============================================================


// FIM DO ESPAÇO PARA O ALUNO


// ============================================================


// Funções de auxílio para o relatório


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


    printf("          RELATORIO DE AVALIACAO AUTOMATICA         \n");


    printf("====================================================\n");


    // Testes das funções


    testar_int("1. eh_par", eh_par(10), 1, "n=10");


    testar_int("2. esta_entre", esta_entre(5, 1, 10), 1, "5 entre 1 e 10");


    testar_int("3. divisivel_por", divisivel_por(10, 0), -1, "10 / 0");


    testar_int("4. dias_mes", quantidade_dias_mes(2), 28, "mes=2");


    testar_int("5. pontuacao", pontuacao(25), 200, "idade=25");


    testar_float("6. desconto", desconto(200.0, 1), 10.0, "valor=200, cat=1");


    testar_int("7. e_bissexto", e_bissexto(1900), 0, "ano=1900");


    testar_float("8. operacao", operacao_matematica(10, 5, '*'), 50.0, "10 * 5");


    testar_int("9. tipo_caracter", tipo_caracter('7'), 1, "caracter='7'");


    testar_int("10. soma_M_m", soma_maior_menor(10, 5, 30), 35, "10, 5, 30");


    printf("====================================================\n");


    return 0;


}