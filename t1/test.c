#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para extrair o domínio e o caminho (paths) da URL
void extract_hostname_and_paths(const char *url, char **hostname, char **paths)
{
    const char *start = strstr(url, "//"); // Procura por "//" para encontrar o início do domínio
    if (start == NULL)
    {
        printf("URL inválida\n");
        return;
    }
    start += 2; // Move o ponteiro para além de "//"

    const char *end = strchr(start, '/'); // Procura pelo próximo '/'
    if (end == NULL)
    {
        printf("URL inválida\n");
        return;
    }

    // Calcula o tamanho necessário para o domínio e aloca memória
    size_t hostname_length = end - start;
    *hostname = (char *)malloc((hostname_length + 1) * sizeof(char)); // +1 para o terminador nulo
    if (*hostname == NULL)
    {
        printf("Erro de alocação de memória\n");
        return;
    }

    // Copia o domínio para a memória alocada
    strncpy(*hostname, start, hostname_length);
    (*hostname)[hostname_length] = '\0'; // Adiciona o terminador nulo

    // Calcula o tamanho necessário para o caminho e aloca memória
    size_t paths_length = strlen(end);
    *paths = (char *)malloc((paths_length + 1) * sizeof(char)); // +1 para o terminador nulo
    if (*paths == NULL)
    {
        printf("Erro de alocação de memória\n");
        free(*hostname); // Libera a memória alocada para o domínio
        return;
    }

    // Copia o caminho para a memória alocada
    strcpy(*paths, end);
}

int main(int argc, char **argv)
{
    char *hostname;
    char *paths;

    extract_hostname_and_paths(argv[1], &hostname, &paths);

    if (hostname != NULL && paths != NULL)
    {
        printf("Domínio: %s\n", hostname);
        printf("Caminho: %s\n", paths);

        // Libera a memória alocada
        free(hostname);
        free(paths);
    }
    return 0;
}
