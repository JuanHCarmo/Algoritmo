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
        printf("Erro ao abrir o arquivo dados.txt.\n");
        return NULL;
    }
    
    *capacidade = 10; // capacidade inicial 
    *qtd_atual = 0; // ainda não leu nada 
    Podcast *vetor = malloc((*capacidade) * sizeof(Podcast));

    if (vetor == NULL){
        printf("Erro ao alocar memória para o vetor.\n");
        fclose(arquivo);
        return NULL;
    }
    
    char linha[500]; // buffer para ler cada linha do arquivo

    fgets(linha, sizeof(linha), arquivo);

    // 3. Ler o restante das linhas que contêm os dados
    while (fgets(linha, sizeof(linha), arquivo) != NULL){
        if (*qtd_atual == (*capacidade)){
            *capacidade = *capacidade * 2; // dobra a capacidade
            Podcast *temp = realloc(vetor, (*capacidade) * sizeof(Podcast));
            if (temp == NULL){
                printf("Erro ao realocar memória para o vetor.\n");
                free(vetor); // libera o bloco de memória alocado anteriormente
                fclose(arquivo);
                return NULL;
            }
            vetor = temp; // Só agora atualiza vetor, com o realloc confirmado 
        }
        Podcast p;

        // CORREÇÃO: Usar sscanf (lendo de 'linha') e não scanf
        int campo_lidos = sscanf(linha, "%99[^;];%149[^;];%199[^;];%f", p.canal, p.titulo, p.participantes, &p.tamanhoMB); 

        if (campo_lidos != 4){
            continue; // pula para a proxima linha se a formatação estiver invalida
        }
        vetor[*qtd_atual] = p; // armazena o podcast no vetor
        (*qtd_atual)++; // incrementa a quantidade atual de podcasts 
    }
    fclose(arquivo);
    return vetor;
}

/* Coleta os dados de um novo podcast e expande a memória se necessário */
void inserir(Podcast **vetor, int *qtd_atual, int *capacidade){
    if (*qtd_atual == *capacidade){
        *capacidade = *capacidade *2; // dobra a capacidade
        Podcast *temp = realloc(*vetor, (*capacidade) * sizeof(Podcast)); // realoca o vetor com a nova capacidade
        if (temp == NULL){
            printf("Erro ao realocar a memória para o vetor.\n");
            return; // sai da função se a realocação falhar
        }
        *vetor = temp; // atualiza o ponteiro que está na main para o novo bloco de memória alocado
    }
    Podcast novo;

    printf("Digite o nome do canal: ");
    fgets(novo.canal, sizeof(novo.canal), stdin);
    novo.canal[strcspn(novo.canal, "\n")] = '\0'; // remove o \n do final do string

    printf("Digite o titulo do episodio: ");
    fgets(novo.titulo, sizeof(novo.titulo), stdin);
    novo.titulo[strcspn(novo.titulo, "\n")] = '\0';  // remove o \n do final do string

    printf("Digite os participantes: ");
    fgets(novo.participantes, sizeof(novo.participantes), stdin);
    novo.participantes[strcspn(novo.participantes, "\n")] = '\0'; // remove o \n do final do string

    printf("Digite o tamanho do episodio em MB: ");
    scanf("%f", &novo.tamanhoMB);
    while (getchar() != '\n'); //limpa o \n que ficou no buffer

    (*vetor)[*qtd_atual] = novo; // armazena o novo podcast no vetor
    (*qtd_atual)++; // incrementa a quantidade atual de podcasts
}

/* Exibe todos os podcasts cadastrados */
void listar(Podcast *vetor, int qtd_atual){
    if (qtd_atual == 0){
        printf("Nenhum podcast cadastrado. \n");
        return;
    }

    // percorre todas as posições ocupadas do vetor (de 0 até qtd_atual - 1) e exibe os dados de cada podcast
    for (int i = 0; i < qtd_atual; i++){
        printf("Canal: %s\n", vetor[i].canal);
        printf("Titulo: %s\n", vetor[i].titulo);
        printf("participantes: %s\n", vetor[i].participantes);
        printf("Tamanho: %.2f MB\n", vetor[i].tamanhoMB);   // exibe o tamanho com duas casas decimais
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
        printf("\nErro: Nao foi possivel abrir o arquivo dados.txt para escrita.\n"); //
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
            while (getchar() != '\n'); // Limpa o buffer do teclado
            continue;
        }
        while (getchar() != '\n'); // Limpa o \n pendente após o scanf

        printf("\n");

        switch (opcao) {
            case 1:
                // Se já houver vetor carregado, libera a memória anterior para evitar vazamento
                if (vetor != NULL) {
                    liberar_memoria(vetor);
                }
                vetor = ler_arquivo(&qtd_atual, &capacidade);
                if (vetor != NULL) {
                    printf("Arquivo lido com sucesso! (%d podcasts carregados)\n", qtd_atual);
                }
                break;

            case 2:
                // Se o vetor ainda não foi inicializado (nem por arquivo, nem por alocação), inicializa com capacidade 10
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
                liberar_memoria(vetor);
                break;

            default:
                printf("Opcao invalida! Escolha um numero de 1 a 6.\n");
        }

    } while (opcao != 6);

    return 0;
}