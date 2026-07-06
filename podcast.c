#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_STR 100

typedef struct {
    char canal[TAM_STR];
    char titulo[TAM_STR];
    char participantes[TAM_STR];
    float tamanhoMB;
} Podcast;

/* Aloca o vetor inicial e carrega os dados do arquivo */
Podcast* ler_arquivo(int *qtd_atual, int *capacidade){
    FILE *arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL){
        // Conforme especificação: se o arquivo não existe, inicia com capacidade 10 e 0 registros
        *capacidade = 10;
        *qtd_atual = 0;
        Podcast *vetor = malloc((*capacidade) * sizeof(Podcast));
        return vetor;
    }
    
    char linha[500]; 

    if (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "%d", qtd_atual);
    } else {
        *qtd_atual = 0;
    }


    *capacidade = (*qtd_atual > 0) ? *qtd_atual : 10; 

    Podcast *vetor = malloc((*capacidade) * sizeof(Podcast));

    if (vetor == NULL){
        printf("Erro ao alocar memória para o vetor.\n");
        fclose(arquivo);
        return NULL;
    }
    
    fgets(linha, sizeof(linha), arquivo);

    int lidos_reais = 0;
    // 3. Ler o restante das linhas que contêm os dados
    while (fgets(linha, sizeof(linha), arquivo) != NULL && lidos_reais < *qtd_atual){
        if (lidos_reais == (*capacidade)){
            *capacidade = *capacidade * 2; // dobra a capacidade
            Podcast *temp = realloc(vetor, (*capacidade) * sizeof(Podcast));
            if (temp == NULL){
                printf("Erro ao realocar memória para o vetor.\n");
                free(vetor); 
                fclose(arquivo); 
                return NULL;
            }
            vetor = temp; 
        }
        Podcast p;

        int campo_lidos = sscanf(linha, "%99[^;];%99[^;];%99[^;];%f", p.canal, p.titulo, p.participantes, &p.tamanhoMB); 

        if (campo_lidos != 4){
            continue; 
        }
        vetor[lidos_reais] = p; 
        lidos_reais++; 
    }
    
    *qtd_atual = lidos_reais;
    fclose(arquivo);
    return vetor;
}

void inserir(Podcast **vetor, int *qtd_atual, int *capacidade){
    if (*qtd_atual == *capacidade){
        *capacidade = *capacidade * 2; // dobra a capacidade
        Podcast *temp = realloc(*vetor, (*capacidade) * sizeof(Podcast)); 
        if (temp == NULL){
            printf("Erro ao realocar a memória para o vetor.\n");
            return; 
        }
        *vetor = temp; 
    }
    Podcast novo;

    printf("Digite o nome do canal: ");
    fgets(novo.canal, sizeof(novo.canal), stdin);
    novo.canal[strcspn(novo.canal, "\n")] = '\0'; 

    printf("Digite o titulo do episodio: ");
    fgets(novo.titulo, sizeof(novo.titulo), stdin);
    novo.titulo[strcspn(novo.titulo, "\n")] = '\0';  

    printf("Digite os participantes: ");
    fgets(novo.participantes, sizeof(novo.participantes), stdin);
    novo.participantes[strcspn(novo.participantes, "\n")] = '\0'; 

    printf("Digite o tamanho do episodio em MB: ");
    scanf("%f", &novo.tamanhoMB);
    while (getchar() != '\n'); 

    (*vetor)[*qtd_atual] = novo; 
    (*qtd_atual)++; 
}

void listar(Podcast *vetor, int qtd_atual){
    if (qtd_atual == 0){
        printf("Nenhum podcast cadastrado. \n");
        return;
    }

    for (int i = 0; i < qtd_atual; i++){
        printf("Canal: %s\n", vetor[i].canal);
        printf("Titulo: %s\n", vetor[i].titulo);
        printf("participantes: %s\n", vetor[i].participantes);
        printf("Tamanho: %.2f MB\n", vetor[i].tamanhoMB);   
        printf("-----------------------------\n");
    }
}


void remover(Podcast *vetor, int *qtd_atual) {
    int indice_usuario, indice_real;

    if (*qtd_atual <= 0) {
        printf("\nErro: Nao existem registros para remover!\n");
        return;
    }

    printf("\nDigite o indice do registro que deseja remover (1 a %d): ", *qtd_atual);
    if (scanf("%d", &indice_usuario) != 1) {
        printf("\nEntrada invalida.\n");
        while (getchar() != '\n'); // Limpa buffer em caso de digitação inválida
        return;
    }

    indice_real = indice_usuario - 1;

    if (indice_real < 0 || indice_real >= *qtd_atual) {
        printf("\nErro: Indice invalido! Escolha um valor entre 1 e %d.\n", *qtd_atual);
        return;
    }

    for (int i = indice_real; i < (*qtd_atual - 1); i++) {
        vetor[i] = vetor[i + 1];
    }

    (*qtd_atual)--;
    
    printf("\nRegistro removido com sucesso!\n");
}

void salvar_arquivo(Podcast *vetor, int qtd_atual) {
    FILE *arquivo = fopen("dados.txt", "w");
    if (arquivo == NULL) {
        printf("\nErro: Nao foi possivel abrir o arquivo dados.txt para escrita.\n"); 
        return;
    }

    fprintf(arquivo, "%d\n", qtd_atual);
    fprintf(arquivo, "Canal; Titulo Episodio; Participantes; TamanhoMB\n");

    for (int i = 0; i < qtd_atual; i++) {
        fprintf(arquivo, "%s;%s;%s;%.2f\n", 
                vetor[i].canal, 
                vetor[i].titulo, 
                vetor[i].participantes, 
                vetor[i].tamanhoMB);
    }

    fclose(arquivo);
    printf("\nDados salvos com sucesso em dados.txt!\n");
}

void liberar_memoria(Podcast *vetor) {
    if (vetor != NULL) {
        free(vetor);
    }
}

int main() {
    Podcast *vetor = NULL;
    int qtd_atual = 0;
    int capacidade = 0;
    int opcao;

    do {
        printf("\n=============================\n");
        printf("        MENU PODCAST         \n");
        printf("=============================\n");
        printf("1. Ler arquivo (dados.txt)\n");
        printf("2. Inserir novo podcast\n");
        printf("3. Listar podcasts\n");
        printf("4. Remover podcast\n");
        printf("5. Salvar arquivo (dados.txt)\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n'); 

        printf("\n");

        switch (opcao) {
            case 1:
                if (vetor != NULL) {
                    liberar_memoria(vetor);
                    vetor = NULL;
                }
                vetor = ler_arquivo(&qtd_atual, &capacidade);
                if (vetor != NULL && qtd_atual > 0) {
                    printf("Arquivo lido com sucesso! (%d podcasts carregados)\n", qtd_atual);
                } else if (vetor != NULL) {
                    printf("Arquivo pronto ou vazio. Pronto para novas inserções!\n");
                }
                break;

            case 2:
                if (vetor == NULL) {
                    capacidade = 10;
                    vetor = malloc(capacidade * sizeof(Podcast));
                    if (vetor == NULL) {
                        printf("Erro ao inicializar memoria do vetor.\n");
                        break;
                    }
                }
                inserir(&vetor, &qtd_atual, &capacidade);
                break;

            case 3:
                listar(vetor, qtd_atual);
                break;

            case 4:
                remover(vetor, &qtd_atual);
                break;

            case 5:
                salvar_arquivo(vetor, qtd_atual);
                break;

            case 6:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opcao invalida! Escolha um numero de 1 a 6.\n");
        }

    } while (opcao != 6);

    if (vetor != NULL) {
        liberar_memoria(vetor);
        vetor = NULL;
    }

    return 0;
}