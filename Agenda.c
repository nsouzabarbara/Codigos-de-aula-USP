#include <stdio.h>
#include <string.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} DATA;

typedef struct {
    int hora;
    int minuto;
    int segundo;
} HORA;

typedef struct {
    DATA data;
    HORA horario;
    char atividade[100];
} AGENDA;


int main() {
    int n, i;
    scanf("%d", &n);
    AGENDA vetorAtividades[n];

    for(i = 0; i < n; i++) {
        scanf("%d", &vetorAtividades[i].data.dia);
        scanf("%d", &vetorAtividades[i].data.mes);
        scanf("%d", &vetorAtividades[i].data.ano);
        scanf("%d", &vetorAtividades[i].horario.hora);
        scanf("%d", &vetorAtividades[i].horario.minuto);
        scanf("%d", &vetorAtividades[i].horario.segundo);
        setbuf(stdin, NULL);
        scanf(" %[^\n]", vetorAtividades[i].atividade);
    }
    for(i = 0; i < n; i++) {
        printf("%02d/%02d/%d - %02d:%02d:%02d\n", vetorAtividades[i].data.dia, vetorAtividades[i].data.mes, vetorAtividades[i].data.ano, vetorAtividades[i].horario.hora, vetorAtividades[i].horario.minuto, vetorAtividades[i].horario.segundo);
        printf("%s", vetorAtividades[i].atividade);
    }
    
    return 0;
}
