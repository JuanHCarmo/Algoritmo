#include <stdio.h>

// Exercício 1
void exercicio1() {
    FILE *arquivo;
    char frase[200];

    arquivo = fopen("nota.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return;
    }

    printf("Digite uma frase:\n");
    fgets(frase, sizeof(frase), stdin);

    fprintf(arquivo, "%s", frase);

    fclose(arquivo);

    printf("Frase salva com sucesso!\n");
}

// Exercício 2
void exercicio2() {
    FILE *arquivo;
    char texto[200];

    arquivo = fopen("nota.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("\nConteudo do arquivo:\n\n");

    while (fgets(texto, sizeof(texto), arquivo) != NULL) {
        printf("%s", texto);
    }

    fclose(arquivo);
}

// Exercício 3
void exercicio3() {
    FILE *arquivo;
    char linha[200];
    int contador = 0;

    arquivo = fopen("poema.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        contador++;
    }

    fclose(arquivo);

    printf("Quantidade de linhas: %d\n", contador);
}

// Exercício 4
void exercicio4() {
    FILE *original;
    FILE *copia;
    char linha[200];

    original = fopen("original.txt", "r");

    if (original == NULL) {
        printf("Erro ao abrir o arquivo original!\n");
        return;
    }

    copia = fopen("copia.txt", "w");

    if (copia == NULL) {
        printf("Erro ao criar o arquivo copia!\n");
        fclose(original);
        return;
    }

    while (fgets(linha, sizeof(linha), original) != NULL) {
        fprintf(copia, "%s", linha);
    }

    fclose(original);
    fclose(copia);

    printf("Arquivo copiado com sucesso!\n");
}

// Exercício 5
void exercicio5() {
    FILE *arquivo;
    char nome[50];
    float nota;
    float soma = 0;
    float media;
    int quantidade = 0;

    arquivo = fopen("alunos.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return;
    }

    printf("Digite os dados de 3 alunos:\n");

    for (int i = 0; i < 3; i++) {
        printf("\nNome: ");
        scanf("%s", nome);

        printf("Nota: ");
        scanf("%f", &nota);

        fprintf(arquivo, "%s %.2f\n", nome, nota);
    }

    fclose(arquivo);

    arquivo = fopen("alunos.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    while (fscanf(arquivo, "%s %f", nome, &nota) != EOF) {
        soma += nota;
        quantidade++;
    }

    fclose(arquivo);

    if (quantidade > 0) {
        media = soma / quantidade;
        printf("\nMedia da turma: %.2f\n", media);
    } else {
        printf("Nenhum aluno encontrado.\n");
    }
}

// Main
int main() {
    int opcao;

    do {
        printf("\n=================================\n");
        printf("   EXERCICIOS COM ARQUIVOS\n");
        printf("=================================\n");
        printf("1 - Criador de Notas\n");
        printf("2 - Leitor de Arquivos\n");
        printf("3 - Contador de Linhas\n");
        printf("4 - Clonador de Arquivos\n");
        printf("5 - Registro de Notas\n");
        printf("0 - Sair\n");
        printf("=================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o ENTER

        printf("\n");

        switch (opcao) {
            case 1:
                exercicio1();
                break;

            case 2:
                exercicio2();
                break;

            case 3:
                exercicio3();
                break;

            case 4:
                exercicio4();
                break;

            case 5:
                exercicio5();
                break;

            case 0:
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}