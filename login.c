#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "arquivos.h"
#include "login.h"

// Função gerada pelo Github Copilot
char* generate_random_string(int length) {
    char* string = malloc((length + 1) * sizeof(char));
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int charset_length = strlen(charset);

    for (int i = 0; i < length; i++) {
        int random_index = rand() % charset_length;
        string[i] = charset[random_index];
    }

    string[length] = '\0';
    return string;
}

// Função gerada com auxílio do Github Copilot
void gera_dados_ord(char nome_dados[], int n)
{
    srand(time(NULL));

    FILE *arq = cria_arq_escrita(nome_dados);

    for (int i = 1; i <= n; i++) {
        char* random_string = generate_random_string(TAM_SENHA);
        fprintf(arq, "%d,%s\n", i, random_string);
        free(random_string);
    }
    fclose(arq);
    puts("Arquivo de base de dados de teste gerado com sucesso");
}

// Função gerada com auxílio do Github Copilot
void gera_dados(char nome_dados[], int n)
{

}

// Função gerada com auxílio do Github Copilot
void gera_testes(char nome_testes[], int n, int p)
{

}