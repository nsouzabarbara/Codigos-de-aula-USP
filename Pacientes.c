#include <stdio.h>
#include <string.h>

typedef struct {
char nome[50];
float altura, peso;
char genero;
int id;
} AGENDA;

int main() {
    int N, i, j, idx;
    scanf("%d", &N);
    AGENDA instancias[N];

    for(i = 0; i < N; i++) {
        scanf(" %[^\n]", instancias[i].nome);
        setbuf(stdin, NULL);
        scanf("%f", &instancias[i].altura);
        scanf("%f", &instancias[i].peso);
        scanf(" %c", &instancias[i].genero);
        scanf("%d", &instancias[i].id);
    }
    for(i = 0; i < N || idx != -1; i++) {
        scanf("%d", &idx);
        for(j = 0; j < N; j++) {
            if(instancias[j].id == idx) {
                printf("nome: %s\n", instancias[j].nome);
                printf("altura: %.2f\n", instancias[j].altura);
                printf("peso: %.2f\n", instancias[j].peso);
                printf("genero: %c\n", instancias[j].genero);
                printf("id: %d\n", instancias[j].id);
                printf("\n");
            }
        }
    }

    return 0;
}
