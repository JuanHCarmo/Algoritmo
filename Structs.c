#include <stdio.h>
#include <math.h>

// ==========================================
// DEFINIÇÃO DAS STRUCTS
// ==========================================

// Definição do Tipo Ponto
typedef struct {
    float x;
    float y;
} Ponto;

// Definição do Tipo Retangulo (composto por dois Pontos)
typedef struct {
    Ponto inferior_esquerdo;
    Ponto superior_direito;
} Retangulo;


// ==========================================
// PROTÓTIPOS DAS FUNÇÕES
// ==========================================
Ponto criar_ponto(float x, float y);
Ponto mover_ponto(Ponto p, float delta_x, float delta_y);
float distancia_pontos(Ponto p1, Ponto p2);
int pontos_iguais(Ponto p1, Ponto p2);
Retangulo criar_retangulo(Ponto inf_esq, Ponto sup_dir);
float calcular_area_retangulo(Retangulo r);
float calcular_perimetro_retangulo(Retangulo r);
int ponto_no_retangulo(Retangulo r, Ponto p);
Retangulo escalar_retangulo(Retangulo r, float fator);
Ponto centro_retangulo(Retangulo r);


// ==========================================
// CORREÇÃO AUTOMATIZADA
// ==========================================
int main() {
    int erros = 0;
    const float EPSILON = 0.001;
    printf("=== INICIANDO TESTES AUTOMATIZADOS ===\n\n");

    // Teste 1: criar_ponto
    Ponto p1 = criar_ponto(1.0, 2.0);
    if (fabs(p1.x - 1.0) > EPSILON || fabs(p1.y - 2.0) > EPSILON) {
        printf("[ERRO] Ex 1: criar_ponto falhou.\n");
        erros++;
    }

    // Teste 2: mover_ponto
    Ponto p2 = criar_ponto(1.0, 1.0);
    Ponto p2_movido = mover_ponto(p2, 3.0, -4.0);
    if (fabs(p2_movido.x - 4.0) > EPSILON || fabs(p2_movido.y - (-3.0)) > EPSILON || fabs(p2.x - 1.0) > EPSILON) {
        printf("[ERRO] Ex 2: mover_ponto falhou (ou alterou o ponto original).\n");
        erros++;
    }

    // Teste 3: distancia_pontos
    Ponto pA = criar_ponto(0.0, 0.0);
    Ponto pB = criar_ponto(3.0, 4.0);
    if (fabs(distancia_pontos(pA, pB) - 5.0) > EPSILON) {
        printf("[ERRO] Ex 3: distancia_pontos falhou.\n");
        erros++;
    }

    // Teste 4: pontos_iguais
    Ponto pC = criar_ponto(1.5, 1.5);
    Ponto pD = criar_ponto(1.5, 1.5);
    if (pontos_iguais(pC, pD) != 1 || pontos_iguais(pA, pC) != 0) {
        printf("[ERRO] Ex 4: pontos_iguais falhou.\n");
        erros++;
    }

    // Teste 5: criar_retangulo
    Ponto inf_esq = criar_ponto(1.0, 1.0);
    Ponto sup_dir = criar_ponto(5.0, 4.0);
    Retangulo ret = criar_retangulo(inf_esq, sup_dir);
    if (fabs(ret.inferior_esquerdo.x - 1.0) > EPSILON || fabs(ret.superior_direito.y - 4.0) > EPSILON) {
        printf("[ERRO] Ex 5: criar_retangulo falhou.\n");
        erros++;
    }

    // Teste 6: calcular_area_retangulo
    if (fabs(calcular_area_retangulo(ret) - 12.0) > EPSILON) {
        printf("[ERRO] Ex 6: calcular_area_retangulo falhou.\n");
        erros++;
    }

    // Teste 7: calcular_perimetro_retangulo
    if (fabs(calcular_perimetro_retangulo(ret) - 14.0) > EPSILON) {
        printf("[ERRO] Ex 7: calcular_perimetro_retangulo falhou.\n");
        erros++;
    }

    // Teste 8: ponto_no_retangulo
    Ponto dentro = criar_ponto(3.0, 2.0);
    Ponto fora = criar_ponto(6.0, 2.0);
    if (ponto_no_retangulo(ret, dentro) != 1 || ponto_no_retangulo(ret, fora) != 0) {
        printf("[ERRO] Ex 8: ponto_no_retangulo falhou.\n");
        erros++;
    }

    // Teste 9: escalar_retangulo
    Retangulo ret_base = criar_retangulo(criar_ponto(0.0, 0.0), criar_ponto(2.0, 2.0));
    Retangulo ret_esc = escalar_retangulo(ret_base, 2.0);
    if (fabs(ret_esc.superior_direito.x - 4.0) > EPSILON || fabs(ret_base.superior_direito.x - 2.0) > EPSILON) {
        printf("[ERRO] Ex 9: escalar_retangulo falhou (ou alterou o original).\n");
        erros++;
    }

    // Teste 10: centro_retangulo
    Ponto centro = centro_retangulo(ret);
    if (fabs(centro.x - 3.0) > EPSILON || fabs(centro.y - 2.5) > EPSILON) {
        printf("[ERRO] Ex 10: centro_retangulo falhou.\n");
        erros++;
    }

    // RESUMO
    if (erros == 0) {
        printf("\n[PARABÉNS!] Todos os 10 testes passaram com sucesso.\n");
    } else {
        printf("\n[ATENÇÃO] Foram encontrados %d erros.\n", erros);
    }
    return 0;
}


// ==========================================
// IMPLEMENTAÇÃO DAS FUNÇÕES
// ==========================================

Ponto criar_ponto(float x, float y) {
    Ponto p;
    p.x = x;
    p.y = y;
    return p;
}

Ponto mover_ponto(Ponto p, float delta_x, float delta_y) {
    Ponto novo_ponto;
    novo_ponto.x = p.x + delta_x;
    novo_ponto.y = p.y + delta_y;
    return novo_ponto;
}

float distancia_pontos(Ponto p1, Ponto p2) {
    float diferenca_x = p1.x - p2.x;
    float diferenca_y = p1.y - p2.y;
    return sqrt((diferenca_x * diferenca_x) + (diferenca_y * diferenca_y));
}

int pontos_iguais(Ponto p1, Ponto p2) {
    if (fabs(p1.x - p2.x) <= 0.001 && fabs(p1.y - p2.y) <= 0.001) {
        return 1;
    } else {
        return 0;
    }
}

Retangulo criar_retangulo(Ponto inf_esq, Ponto sup_dir) {
    Retangulo r;
    r.inferior_esquerdo = inf_esq;
    r.superior_direito = sup_dir;
    return r;
}

float calcular_area_retangulo(Retangulo r) {
    float largura;
    float altura;

    largura = r.superior_direito.x - r.inferior_esquerdo.x;
    altura = r.superior_direito.y - r.inferior_esquerdo.y;

    return largura * altura;
}

float calcular_perimetro_retangulo(Retangulo r) {
    float largura;
    float altura;

    largura = r.superior_direito.x - r.inferior_esquerdo.x;
    altura = r.superior_direito.y - r.inferior_esquerdo.y;

    return 2 * (largura + altura);
}

int ponto_no_retangulo(Retangulo r, Ponto p) {
    if (p.x >= r.inferior_esquerdo.x && p.x <= r.superior_direito.x &&
        p.y >= r.inferior_esquerdo.y && p.y <= r.superior_direito.y) {
        return 1;
    } else {
        return 0;
    }
}

Retangulo escalar_retangulo(Retangulo r, float fator) {
    float largura;
    float altura;

    largura = r.superior_direito.x - r.inferior_esquerdo.x;
    altura = r.superior_direito.y - r.inferior_esquerdo.y;

    float nova_largura = largura * fator;
    float nova_altura = altura * fator;

    Ponto novo_sup_dir = criar_ponto(r.inferior_esquerdo.x + nova_largura, r.inferior_esquerdo.y + nova_altura);

    return criar_retangulo(r.inferior_esquerdo, novo_sup_dir);
}

Ponto centro_retangulo(Retangulo r) {
    float centro_x = (r.inferior_esquerdo.x + r.superior_direito.x) / 2;
    float centro_y = (r.inferior_esquerdo.y + r.superior_direito.y) / 2;
    return criar_ponto(centro_x, centro_y);
}