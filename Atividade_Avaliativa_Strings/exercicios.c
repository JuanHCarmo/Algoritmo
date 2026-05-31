#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "exercicios.h"

int contar_palavras(char str[]) {
    int cont = 0, i = 0, dentro = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.' || str[i] == ';') {
            dentro = 0;
        } else if (dentro == 0) {
            dentro = 1;
            cont++;
        }
    }
    return cont;
}

void extrair_usuario(char email[], char res[]) {
    int i = 0;
    while (email[i] != '@' && email[i] != '\0') {
        res[i] = email[i];
        i++;
    }
    res[i] = '\0';
}

void extrair_dominio(char email[], char res[]) {
    int i = 0, j = 0, achou = 0;
    while (email[i] != '\0') {
        if (achou) {
            res[j++] = email[i];
        }
        if (email[i] == '@') achou = 1;
        i++;
    }
    res[j] = '\0';
}

int maior_palavra(char str[]) {
    int maior = 0, atual = 0, i = 0;
    while (1) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.' || str[i] == ';' || str[i] == '\0') {
            if (atual > maior) maior = atual;
            atual = 0;
            if (str[i] == '\0') break;
        } else {
            atual++;
        }
        i++;
    }
    return maior;
}

void enxugar_espacos(char str[]) {
    int i, j = 0, espaco = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            str[j++] = str[i];
            espaco = 0;
        } else if (espaco == 0) {
            str[j++] = ' ';
            espaco = 1;
        }
    }
    str[j] = '\0';
}

int termina_com(char str[], char sufixo[]) {
    int t_str = strlen(str), t_suf = strlen(sufixo);
    if (t_suf > t_str) return 0;
    for (int i = 0; i < t_suf; i++) {
        if (str[t_str - t_suf + i] != sufixo[i]) return 0;
    }
    return 1;
}

int contar_char(char str[], char alvo) {
    int c = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == alvo) c++;
    }
    return c;
}

void inverte_letras(char str[]) {
    int i = 0, j = strlen(str) - 1;
    while (i < j) {
        if (!isalpha(str[i])) i++;
        else if (!isalpha(str[j])) j--;
        else {
            char tmp = str[i];
            str[i] = str[j];
            str[j] = tmp;
            i++; j--;
        }
    }
}

void formatar_citacao(char nome[], char res[]) {
    int i, u = -1, tam = strlen(nome);
    for (i = 0; i < tam; i++) if (nome[i] == ' ') u = i;
    if (u != -1) {
        int k = 0;
        for (i = u + 1; i < tam; i++) res[k++] = nome[i];
        res[k++] = ','; res[k++] = ' ';
        res[k++] = nome[0]; res[k++] = '.'; res[k] = '\0';
    } else strcpy(res, nome);
}

int senha_forte(char senha[]) {
    int mai = 0, num = 0, tam = strlen(senha);
    if (tam < 8) return 0;
    for (int i = 0; i < tam; i++) {
        if (senha[i] >= 'A' && senha[i] <= 'Z') mai = 1;
        if (senha[i] >= '0' && senha[i] <= '9') num = 1;
    }
    return (mai && num);
}