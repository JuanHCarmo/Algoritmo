#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef struct {
    char canal[100];
    char titulo[150];
    char participantes[200]; // Pode ser vazio
    float tamanho_mb;        // Deve ser >= 0
} Podcast;



/* Aloca o vetor inicial e carrega os dados do arquivo */
Podcast* ler_arquivo(int *qtd_atual, int *capacidade){
    FILE *arquivo = fopen("arquivo.csv", "r");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo.\n");
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

    while (fgets(linha, sizeof(linha), arquivo) != NULL){
        if (*qtd_atual == (*capacidade)){
            *capacidade = *capacidade * 2; // dobra a capacidade
            Podcast *temp = realloc(vetor, (*capacidade) * sizeof(Podcast));
            if (temp == NULL){
                printf("Erro ao realocar memória para o vetor.\n");
                free(vetor);         //  libera o bloco de memória alocafo anteriormente
                fclose(arquivo);
                return NULL;
            }
            vetor = temp;  // Só agora atualiza vetor, com o realloc confirmado 
        }
        Podcast p;

        // Verificar se os campos foram lidos corretamente
        int campo_lidos = sscanf(linha, "%99[^;];%149[^;];%199[^;];%f", p.canal, p.titulo, p.participantes, &p.tamanho_mb); 
         

        if (campo_lidos != 4){
            continue; // pula para a proxima linha se a formatação estiver invalida
        }
        vetor[*qtd_atual] = p; // armazena o podcast no vetor
        (*qtd_atual) ++; // incrementa a quantidade atual de podcasts 
    }
    fclose(arquivo);
    return (vetor);

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
    scanf("%f", &novo.tamanho_mb);
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
        printf("Tamanho: %.2f MB\n", vetor[i].tamanho_mb);   // exibe o tamanho com duas casas decimais
        printf("-----------------------------\n");
    }
}