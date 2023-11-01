#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Artista
{
    char nome[100];
    char genero[100];
    char local[100];
    char **albums;
    int num_albums;
};

// Função para ler um artista do arquivo
struct Artista lerArtista(FILE *arquivo)
{
    struct Artista artista;
    char linha[100];

    if (fgets(artista.nome, sizeof(artista.nome), arquivo) == NULL)
    {
        strcpy(artista.nome, "FIM"); 
        return artista;
    }

    artista.nome[strcspn(artista.nome, "\n")] = '\0'; 
    fgets(artista.genero, sizeof(artista.genero), arquivo);
    artista.genero[strcspn(artista.genero, "\n")] = '\0'; 
    fgets(artista.local, sizeof(artista.local), arquivo);
    artista.local[strcspn(artista.local, "\n")] = '\0'; 

    artista.num_albums = 0;
    artista.albums = NULL;

    while (1)
    {
        if (fgets(linha, sizeof(linha), arquivo) == NULL || strcmp(linha, "==========\n") == 0)
        {
            break;
        }
        artista.num_albums++;
        artista.albums = (char **)realloc(artista.albums, artista.num_albums * sizeof(char *));
        artista.albums[artista.num_albums - 1] = strdup(linha);
    }

    return artista;
}

void imprimirArtista(struct Artista artista)
{
    printf("Nome: %s\n", artista.nome);
    printf("Genero: %s\n", artista.genero);
    printf("Local: %s\n", artista.local);
    printf("Albuns:\n");
    for (int i = 0; i < artista.num_albums; i++)
    {
        printf("%s", artista.albums[i]);
    }
    printf("==========\n");
}

void inserirArtista(struct Artista novoArtista, struct Artista **artistas, int *num_artistas)
{
    *artistas = (struct Artista *)realloc(*artistas, (*num_artistas + 1) * sizeof(struct Artista));

    int posicao = 0;
    while (posicao < *num_artistas && strcmp(novoArtista.nome, (*artistas)[posicao].nome) > 0)
    {
        posicao++;
    }

    for (int i = *num_artistas; i > posicao; i--)
    {
        (*artistas)[i] = (*artistas)[i - 1];
    }

    (*artistas)[posicao] = novoArtista;

    (*num_artistas)++;

    printf("Artista foi inserido com sucesso!\n");
}

void buscarArtista(char *nomeArtista, struct Artista *artistas, int num_artistas)
{
    nomeArtista[strcspn(nomeArtista, "\n")] = '\0';

    int encontrado = 0;
    int inicio = 0;
    int fim = num_artistas - 1;

    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;
        int comparacao = strcmp(nomeArtista, artistas[meio].nome);
        if (comparacao == 0)
        {
            printf("\nArtista foi encontrado:\n");
            imprimirArtista(artistas[meio]);
            encontrado = 1;
            break;
        }
        else if (comparacao < 0)
        {
            fim = meio - 1;
        }
        else
        {
            inicio = meio + 1;
        }
    }

    if (!encontrado)
    {
        printf("Artista nao foi encontrado.\n");
    }
}

int main()
{
    FILE *arquivo;
    struct Artista *artistas = NULL;
    int num_artistas = 0;

    arquivo = fopen("C:\\Users\\leona\\OneDrive\\Área de Trabalho\\Lista1\\artistas.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    while (!feof(arquivo))
    {
        struct Artista artista = lerArtista(arquivo);
        if (strcmp(artista.nome, "FIM") != 0)
        {
            artistas = (struct Artista *)realloc(artistas, (num_artistas + 1) * sizeof(struct Artista));
            artistas[num_artistas] = artista;
            num_artistas++;
        }
    }

    fclose(arquivo);

    int escolha;
    char nomeArtista[100];

    do
    {
        printf("\nMenu:\n");
        printf("1. Inserir artista\n");
        printf("2. Buscar artista\n");
        printf("3. Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &escolha);

        // Limpar o buffer do teclado
        while (getchar() != '\n')
            ;

        switch (escolha)
        {
        case 1:
            printf("Digite os detalhes do novo artista (ou digite 'FIM' para parar):\n");
            struct Artista novoArtista;
            printf("Nome: ");
            getchar();
            fgets(novoArtista.nome, sizeof(novoArtista.nome), stdin);
            novoArtista.nome[strcspn(novoArtista.nome, "\n")] = '\0';
            printf("Genero: ");
            fgets(novoArtista.genero, sizeof(novoArtista.genero), stdin);
            novoArtista.genero[strcspn(novoArtista.genero, "\n")] = '\0';
            printf("Local: ");
            fgets(novoArtista.local, sizeof(novoArtista.local), stdin);
            novoArtista.local[strcspn(novoArtista.local, "\n")] = '\0';
            printf("Albuns (insira um por linha, digite 'FIM' para parar):\n");
            novoArtista.num_albums = 0;
            novoArtista.albums = NULL;
            char album[100];
            while (1)
            {
                fgets(album, sizeof(album), stdin);
                album[strcspn(album, "\n")] = '\0';
                if (strcmp(album, "FIM") == 0)
                {
                    break;
                }
                novoArtista.num_albums++;
                novoArtista.albums = (char **)realloc(novoArtista.albums, novoArtista.num_albums * sizeof(char *));
                novoArtista.albums[novoArtista.num_albums - 1] = strdup(album);
            }
            inserirArtista(novoArtista, &artistas, &num_artistas);
            break;

        case 2:
            printf("Digite o nome do artista a ser buscado: ");
            getchar();
            fgets(nomeArtista, sizeof(nomeArtista), stdin);
            buscarArtista(nomeArtista, artistas, num_artistas);
            break;

        case 3:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (escolha != 3);

    for (int i = 0; i < num_artistas; i++)
    {
        for (int j = 0; j < artistas[i].num_albums; j++)
        {
            free(artistas[i].albums[j]);
        }
        free(artistas[i].albums);
    }
    free(artistas);

    return 0;
}
