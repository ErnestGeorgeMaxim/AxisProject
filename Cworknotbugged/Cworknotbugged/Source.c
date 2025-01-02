#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

struct Carte
{
    char autor[50];
    char titlu[50];
    int anul_publicarii;
};

typedef struct Carte Carte;

int citireCartiFisier(Carte *C, int n)
{
    FILE* fis_in = fopen("Raft.txt", "r");
    if (!fis_in)
    {
        printf("Fisierul Raft.txt nu s-a deschis!");
        return 0;
    }
    fscanf(fis_in, "%d", &n);
    C = (Carte*)malloc(n * sizeof(Carte));
    if (!C)
    {
        perror("Sirul nu s-a alocat");
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        fscanf(fis_in, "%s", &C[i].autor);
        fscanf(fis_in, "%s", &C[i].titlu);
        fscanf(fis_in, "%d", &C[i].anul_publicarii);
    }
    fclose(fis_in);
    return 1;
}

int main()
{
    Carte* C;
    int n;
    citireCartiFisier(&C, n);
    printf("%d\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", C[i].autor);
        printf("%s\n", C[i].titlu);
        printf("%d\n", C[i].anul_publicarii);
    }
    free(C);

    return 0;
}
