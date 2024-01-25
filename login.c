#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "arquivos.h"
#include "login.h"

// Função gerada pelo Github Copilot
char* generate_random_string(unsigned length) {
    char* string = malloc((length + 1) * sizeof(char));
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int charset_length = strlen(charset);

    for (unsigned i = 0; i < length; i++) {
        int random_index = rand() % charset_length;
        string[i] = charset[random_index];
    }

    string[length] = '\0';
    return string;
}

// Função gerada com auxílio do Github Copilot
void gera_dados_ord(char nome_dados[], int n)
{
    srand((unsigned int)time(NULL));

    FILE *arq = cria_arq_escrita(nome_dados);

    for (int i = 1; i <= n; i++) {
        char* random_string = generate_random_string(TAM_SENHA);
        fprintf(arq, "%d,%s\n", i, random_string);
        free(random_string);
    }
    fclose(arq);
    puts("Arquivo de base de dados de teste gerado com sucesso");
}

// Struct to hold the id and the random string
typedef struct {
    int id;
    char* string;
} Data;

// Function to shuffle an array of Data
void shuffle_data(Data* array, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Data temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// Função gerada com auxílio do Github Copilot
void gera_dados(char nome_dados[], int n) {
    srand((unsigned int)time(NULL));

    // Create and fill the array with data in order
    Data* data = malloc((size_t)n * sizeof(Data));
    for (int i = 0; i < n; i++) {
        data[i].id = i + 1;
        data[i].string = generate_random_string(TAM_SENHA);
    }

    // Shuffle the array
    shuffle_data(data, n);

    // Write the shuffled data to the file
    FILE *arq = cria_arq_escrita(nome_dados);
    for (int i = 0; i < n; i++) {
        fprintf(arq, "%d,%s\n", data[i].id, data[i].string);
        free(data[i].string);
    }
    fclose(arq);
    free(data);

    puts("Arquivo de base de dados de teste desordenado gerado com sucesso");
}

// Função gerada com auxílio do Github Copilot
void gera_testes(char nome_testes[], int n, int p)
{

}