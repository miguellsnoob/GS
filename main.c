
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_RELATOS 100
#define PI 3.14159265358979323846
#define RAIO_TERRA_KM 6371.0

typedef struct {
    char nome[50];
    char email[50];
    char tipo_catastrofe[30];
    char data[11]; // "DD/MM/AAAA"
    float latitude;
    float longitude;
    char descricao[200];
} Relato;

// Função para calcular distância entre dois pontos usando fórmula de Haversine
float calcularDistancia(float lat1, float lon1, float lat2, float lon2) {
    float dlat = (lat2 - lat1) * PI / 180.0;
    float dlon = (lon2 - lon1) * PI / 180.0;
    lat1 = lat1 * PI / 180.0;
    lat2 = lat2 * PI / 180.0;

    float a = pow(sin(dlat / 2), 2) + 
              pow(sin(dlon / 2), 2) * cos(lat1) * cos(lat2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return RAIO_TERRA_KM * c;
}

void cadastrarRelato(Relato relatos[], int *qtd) {
    if (*qtd >= MAX_RELATOS) {
        printf("Limite de relatos atingido!\n");
        return;
    }

    Relato r;

    printf("Nome: ");
    fgets(r.nome, sizeof(r.nome), stdin);
    r.nome[strcspn(r.nome, "\n")] = 0;

    printf("Email: ");
    fgets(r.email, sizeof(r.email), stdin);
    r.email[strcspn(r.email, "\n")] = 0;

    printf("Tipo de catástrofe: ");
    fgets(r.tipo_catastrofe, sizeof(r.tipo_catastrofe), stdin);
    r.tipo_catastrofe[strcspn(r.tipo_catastrofe, "\n")] = 0;

    printf("Data (DD/MM/AAAA): ");
    fgets(r.data, sizeof(r.data), stdin);
    r.data[strcspn(r.data, "\n")] = 0;

    printf("Latitude: ");
    scanf("%f", &r.latitude);

    printf("Longitude: ");
    scanf("%f", &r.longitude);
    getchar(); // limpar buffer

    printf("Descrição: ");
    fgets(r.descricao, sizeof(r.descricao), stdin);
    r.descricao[strcspn(r.descricao, "\n")] = 0;

    relatos[*qtd] = r;
    (*qtd)++;
    printf("Relato cadastrado com sucesso!\n");
}

void listarRelatos(Relato relatos[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\nRelato #%d:\n", i + 1);
        printf("Nome: %s\n", relatos[i].nome);
        printf("Email: %s\n", relatos[i].email);
        printf("Tipo: %s\n", relatos[i].tipo_catastrofe);
        printf("Data: %s\n", relatos[i].data);
        printf("Localização: %.4f, %.4f\n", relatos[i].latitude, relatos[i].longitude);
        printf("Descrição: %s\n", relatos[i].descricao);
    }
}

void consultarPorRaio(Relato relatos[], int qtd, float latRef, float lonRef) {
    printf("\nRelatos em um raio de 10 km:\n");
    for (int i = 0; i < qtd; i++) {
        float distancia = calcularDistancia(latRef, lonRef, relatos[i].latitude, relatos[i].longitude);
        if (distancia <= 10.0) {
            printf("\nRelato #%d (%.2f km):\n", i + 1, distancia);
            printf("Nome: %s\n", relatos[i].nome);
            printf("Tipo: %s\n", relatos[i].tipo_catastrofe);
            printf("Data: %s\n", relatos[i].data);
            printf("Descrição: %s\n", relatos[i].descricao);
        }
    }
}

void salvarRelatos(Relato relatos[], int qtd, const char *arquivo) {
    FILE *f = fopen(arquivo, "w");
    if (!f) {
        printf("Erro ao salvar arquivo.\n");
        return;
    }
    for (int i = 0; i < qtd; i++) {
        fprintf(f, "%s|%s|%s|%s|%f|%f|%s\n",
            relatos[i].nome,
            relatos[i].email,
            relatos[i].tipo_catastrofe,
            relatos[i].data,
            relatos[i].latitude,
            relatos[i].longitude,
            relatos[i].descricao);
    }
    fclose(f);
    printf("Relatos salvos com sucesso!\n");
}

void carregarRelatos(Relato relatos[], int *qtd, const char *arquivo) {
    FILE *f = fopen(arquivo, "r");
    if (!f) return;

    while (!feof(f) && *qtd < MAX_RELATOS) {
        Relato r;
        fscanf(f, "%49[^|]|%49[^|]|%29[^|]|%10[^|]|%f|%f|%199[^\n]\n",
               r.nome, r.email, r.tipo_catastrofe, r.data,
               &r.latitude, &r.longitude, r.descricao);
        relatos[*qtd] = r;
        (*qtd)++;
    }
    fclose(f);
}

int main() {
    Relato relatos[MAX_RELATOS];
    int qtd = 0;
    int opcao;
    float latRef, lonRef;

    carregarRelatos(relatos, &qtd, "relatos.txt");

    do {
        printf("\n===== SISTEMA DE RELATOS =====\n");
        printf("1. Cadastrar relato\n");
        printf("2. Listar relatos\n");
        printf("3. Consultar por raio (10 km)\n");
        printf("4. Salvar e sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpa buffer

        switch (opcao) {
            case 1:
                cadastrarRelato(relatos, &qtd);
                break;
            case 2:
                listarRelatos(relatos, qtd);
                break;
            case 3:
                printf("Informe sua latitude: ");
                scanf("%f", &latRef);
                printf("Informe sua longitude: ");
                scanf("%f", &lonRef);
                consultarPorRaio(relatos, qtd, latRef, lonRef);
                getchar(); // limpar buffer
                break;
            case 4:
                salvarRelatos(relatos, qtd, "relatos.txt");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 4);

    return 0;
}
