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

// Function to shuffle an array of Login
void shuffle_data(Login* array, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Login temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// Função gerada com auxílio do Github Copilot
void gera_dados(char nome_dados[], char nome_dados_ord[], int n) {
    srand((unsigned int)time(NULL));

    // Create and fill the array with data in order
    Login* data = malloc((size_t)n * sizeof(Login));
    for (int i = 0; i < n; i++) {
        data[i].usr = i + 1;
        strcpy(data[i].senha, generate_random_string(TAM_SENHA));
    }

    // Escreve os dados ordenados no arquivo
    FILE *arq = cria_arq_escrita(nome_dados_ord);
    for (int i = 0; i < n; i++) {
        fprintf(arq, "%d,%s\n", data[i].usr, data[i].senha);
    }

    // Shuffle the array
    shuffle_data(data, n);

    // Write the shuffled data to the file
    FILE *arq1 = cria_arq_escrita(nome_dados);
    for (int i = 0; i < n; i++) {
        fprintf(arq1, "%d,%s\n", data[i].usr, data[i].senha);
    }
    fclose(arq);
    fclose(arq1);
    free(data);

    puts("Arquivos de base de dados gerados com sucesso");
}

// Função gerada com auxílio do Github Copilot
void gera_testes(char nome_dados[], char nome_testes[], int nd, int n, int p) {
    srand((unsigned int)time(NULL));

    // Calculate the number of wrong inputs
    int wrong_inputs = (n * p) / 100;

    // Open the file for writing
    FILE *arq = cria_arq_escrita(nome_testes);

    for (int i = 0; i < n; i++) {
        int id = rand() % nd + 1;  // Generate a random id
        char* string;

        if (i < wrong_inputs) {
            // Generate a wrong input
            string = generate_random_string(TAM_SENHA);
        } else {
            // Generate a correct input
            string = get_string_for_id(nome_dados, id);
        }

        fprintf(arq, "%d,%s\n", id, string);
        free(string);
    }

    fclose(arq);

    puts("Arquivo de testes gerado com sucesso");
}

char* get_string_for_id(char nome_dados[], int id) {

    FILE *arq = carrega_arq_leitura(nome_dados);

    char line[TAM_LINHA];
    while (fgets(line, sizeof(line), arq)) {
        int current_id;
        char string[TAM_MAX_SENHA];

        // Parse the line
        if (sscanf(line, "%d,%s", &current_id, string) != 2) {
            continue;  // Invalid line, skip it
        }

        // Check if the id matches
        if (current_id == id) {
            fclose(arq);

            // Return a copy of the string
            char* result = malloc((strlen(string) + 1) * sizeof(char));
            strcpy(result, string);
            return result;
        }
    }

    fclose(arq);
    return NULL;  // No match found
}