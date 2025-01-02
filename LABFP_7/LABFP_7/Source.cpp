#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

/*

4 5
1 1 2 3
5 7 9 1 4
3 1 5 3 1
9 8 4 3 1
7 1 1 0 4

*/

void afisareSubMatrice(int n, int m, float** mat);
int alocareMatrice(int n, int m, float*** mat);
void citireMatrice(int n, int m, float** mat);
void atribuireSubMatrice(int n, int m, float*** mat, float*** sub_mat, int is, int js);
int getMatrice(int n, int m, float*** mat, int is, int js, int ie, int je, float*** sub_mat, int* n_sub, int* m_sub);

int main()
{
    float** mat, ** sub_mat;
    int n, m, is, ie, js, je, n_sub, m_sub;
    scanf("%d%d", &n, &m);
    scanf("%d%d%d%d", &is, &js, &ie, &je);
    alocareMatrice(n, m, &mat);
    citireMatrice(n, m, mat);
    if (!getMatrice(n, m, &mat, is, js, ie, je, &sub_mat, &n_sub, &m_sub))
        printf("Eroare! \n");
    else
    {
        afisareSubMatrice(n_sub, m_sub, sub_mat);
        for (int i = 0; i < n_sub; i++)
            free(sub_mat[i]);
        free(sub_mat);
    }
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
    return 0;
}

int getMatrice(int n, int m, float*** mat, int is, int js, int ie, int je, float*** sub_mat, int* n_sub, int* m_sub)
{
    *n_sub = ie - is + 1;
    *m_sub = je - js + 1;
    if (!alocareMatrice(*n_sub, *m_sub, sub_mat))
        return 0;
    else
    {
        atribuireSubMatrice(*n_sub, *m_sub, mat, sub_mat, is, js);
        return 1;
    }
}

int alocareMatrice(int n, int m, float*** mat)
{
    *mat = (float**)malloc(n * sizeof(float*));
    if (!*mat)
        return 0;
    for (int i = 0; i < n; i++)
    {
        (*mat)[i] = (float*)malloc(m * sizeof(float));
        if (!(*mat)[i])
        {
            for (int j = 0; j < i; j++)
                free((*mat)[j]);
            free(*mat);
            *mat = NULL;
            return 0;
        }
    }
    return 1;
}

void citireMatrice(int n, int m, float** mat)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            scanf("%f", &mat[i][j]);
    }
}

void atribuireSubMatrice(int n, int m, float*** mat, float*** sub_mat, int is, int js)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            (*sub_mat)[i][j] = (*mat)[i + is][j + js];
}

void afisareSubMatrice(int n, int m, float** mat)
{
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%.0f ", mat[i][j]);
        printf("\n");
    }
}