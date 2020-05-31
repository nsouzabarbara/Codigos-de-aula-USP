#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLUNAS 5

typedef struct {
    int classe, nUSP;
    char nome[16], sobrenome[16];
    float P1, P2, trabalho, mediaFinal;
} Student;

void read_student (Student* student, int number_of_students, int total_students, int c);
void print_student (Student* student, int pos);
Student* allocate_StudentArray (int number_of_students);
void realloc_StudentArray (Student* student, int total_students, int number_of_students);
void search_StudentByName (Student* student, int pos, int num, char name[16], char last_name[16]);
float** allocate_statistics (int c);
float** realloc_statistics (int c, float** statistics);
void generate_statistics (int c, Student* student, int total_students, int number_of_students, float** statistics);
void free_statistics (float** statistics, int c);
void print_statistics (float** statistics);
Student* create_class (int c, float** statistics, int number_of_students, int total_students);
Student* realloc_class (Student* student, int c, float** statistics, int number_of_students, int total_students);
void save_data (float** statistics, int c);

int main(){

    int c = 1, total_students = 0, opcao, number_of_students;
    float** statistics = NULL;
    Student* student;
    char name[16], last_name[16];

    while (1){
        printf("                      *~ MENU ~*                          \n");
        printf(" 1 - Criar turma;                                         \n");
        printf(" 2 - Procurar aluno;                                      \n");
        printf(" 3 - Gerar estatisticas das turmas;                       \n");
        printf(" 4 - Gravar informacoes de uma turma;                     \n");
        printf(" 5 - Encerrar sistema;                                    \n");
        printf(" Digite sua opcao = "); scanf ("%d", &opcao);

        switch (opcao){
            case 1:
                printf("                        TURMA %d                       \n", c);
                printf("Numero de alunos da turma: ");
                scanf("%d", &number_of_students);
                printf("\n");
                
                if (c == 1){                                                            
                    statistics = allocate_statistics(c);
                    student = create_class(c, statistics, number_of_students, total_students);
                }
                else{
                    statistics = realloc_statistics(c, statistics);
                    student = realloc_class(student, c, statistics, number_of_students, total_students);
                }
                c++;
                total_students = total_students + number_of_students;
                break;
            case 2: 
                printf("\n");
                printf("Digite o nome completo do aluno que procura: ");
                scanf("%s %s", name, last_name);
                search_StudentByName(student, (total_students - 1), (total_students - 1), name, last_name);
                break;
            case 3:
                print_statistics (statistics);
                break;
            case 4:
                save_data (statistics, c);                
                break;
            case 5:
                free_statistics (statistics, c);
                free(student);
                printf("                        FIM                        \n");
                return 0;
            default:
                printf("Opcao invalida!! Tente novamente.");
                break;
        }
    }   
}

void read_student (Student *student, int number_of_students, int total_students, int c){
    int count = 1;

    for(int i = total_students; i < (number_of_students + total_students); i++){
        printf("\n                        ALUNO %d                        \n", count);
        student[i].classe = c;
        printf("Nome do aluno: ");
        scanf("%s", student[i].nome);
        printf("Sobrenome do aluno: ");
        scanf("%s", student[i].sobrenome);
        printf("Numero USP: ");
        scanf("%d", &student[i].nUSP);
        printf("Nota da primeira prova: ");
        scanf("%f", &student[i].P1);
        printf("Nota da segunda prova: ");
        scanf("%f", &student[i].P2);
        printf("Nota do trabalho: ");
        scanf("%f", &student[i].trabalho);
        student[i].mediaFinal = (float) (student[i].P1 + student[i].P2 + student[i].trabalho)/3;
        count++;
    }
}

void print_student (Student *student, int pos){
    printf("\n");
    printf("Turma: %d\n", student[pos].classe);
    printf("Nome completo do aluno: %s %s\n", student[pos].nome, student[pos].sobrenome);
    printf("Numero USP: %d\n", student[pos].nUSP);
    printf("Nota da primeira prova: %.1f\n", student[pos].P1);
    printf("Nota da segunda prova: %.1f\n", student[pos].P2);
    printf("Nota do trabalho: %.1f\n", student[pos].trabalho);
    printf("Media: %.2f\n", student[pos].mediaFinal);
    printf("\n");
}

Student* allocate_StudentArray (int number_of_students){
    Student* student = (Student*) malloc (number_of_students * sizeof(Student));
    return student;
}

void realloc_StudentArray (Student* student, int total_students, int number_of_students){
    student = (Student*) realloc (student, (total_students + number_of_students) * sizeof(Student));
}

float** allocate_statistics (int c){
    float** statistics = (float**) malloc(c * sizeof(float*));
    for(int i = 0; i < c; i++){
        statistics [i] = (float*) malloc(COLUNAS * sizeof(float));
    }
    return statistics;
}

float** realloc_statistics (int c, float** statistics){
    statistics = (float **) realloc (statistics, c * sizeof(float *));
    statistics[c - 1] = (float*) malloc(COLUNAS * sizeof(float));

    return statistics;
}

void search_StudentByName (Student* student, int pos, int num, char name[16], char last_name[16]){

    if (pos == -1){
        printf("Aluno nao encontrado.\n");
    }
    else if (strncmp(name, student[pos].nome, strlen(student[pos].nome)) == 0 && strncmp(last_name, student[pos].sobrenome, strlen(student[pos].sobrenome)) == 0){
        print_student(student, pos);
    }
    else {
        pos--;
        search_StudentByName(student, pos, num, name, last_name);
    }
}

void generate_statistics (int c, Student* student, int total_students, int number_of_students, float** statistics){
    float soma_p1 = 0;
    float soma_p2 = 0;
    float soma_trab = 0;
    float soma_med = 0;
    float soma_aprovados = 0;

    for (int i = total_students; i < (number_of_students + total_students); i++){
        soma_p1 = soma_p1 + student[i].P1;
        soma_p2 = soma_p2 + student[i].P2;
        soma_trab = soma_trab + student[i].trabalho;
        soma_med = soma_med + student[i].mediaFinal;
        if (student[i].mediaFinal >= 5) soma_aprovados++;
    }

    statistics[c - 1][0] = (float) soma_p1/number_of_students; 
    statistics[c - 1][1] = (float) soma_p2/number_of_students;
    statistics[c - 1][2] = (float) soma_trab/number_of_students;
    statistics[c - 1][3] = (float) soma_med/number_of_students;
    statistics[c - 1][4] = (float) soma_aprovados/number_of_students;
}

void free_statistics (float** statistics, int c){
    for (int i = 0; i < c; i++){
        free (statistics[i]);
    }
    free (statistics);
}

void print_statistics (float** statistics){
    int number_of_class;

    printf("\n");
    printf("Digite o numero da turma que deseja: ");
    scanf("%d", &number_of_class);

    printf("                        TURMA %d                        \n", number_of_class);
    printf("Media P1: %.1f\n", statistics[number_of_class - 1][0]);
    printf("Media P2: %.1f\n", statistics[number_of_class - 1][1]);
    printf("Media Trabalho: %.1f\n", statistics[number_of_class - 1][2]);
    printf("Media Final: %.2f\n", statistics[number_of_class - 1][3]);
    printf("Aprovacao: %.1f\n", (statistics[number_of_class - 1][4])*100);
    printf("\n");
}

Student* create_class (int c, float** statistics, int number_of_students, int total_students){
    Student* student = allocate_StudentArray(number_of_students);
    
    printf("           *~ Entre com os dados dos alunos ~*            \n");
    read_student(student, number_of_students, total_students, c);

    generate_statistics (c, student, total_students, number_of_students, statistics);

    return student;
}

Student* realloc_class (Student* student, int c, float** statistics, int number_of_students, int total_students){
    realloc_StudentArray (student, total_students, number_of_students);

    printf("           *~ Entre com os dados dos alunos ~*            \n");
    read_student(student, number_of_students, total_students, c);

    generate_statistics (c, student, total_students, number_of_students, statistics);

    return student;
}

void save_data (float** statistics, int c){
    char name_file[30];

    for (int i = 0; i < (c - 1); i++){
        printf("Nome do arquivo da turma %d: ", i+1);
        scanf("%s", name_file);

        FILE* arquivo = fopen(name_file, "w");

        if (arquivo == NULL) printf("Erro na criacao do arquivo.\n");

        else {
            fprintf(arquivo, "Turma %d\n", i + 1);
            fprintf(arquivo, "Media P1: %.2f\n", statistics[i][0]);
            fprintf(arquivo, "Media P2: %.2f\n", statistics[i][1]);
            fprintf(arquivo, "Media Trabalho: %.2f\n", statistics[i][2]);
            fprintf(arquivo, "Media final: %.2f\n", statistics[i][3]);
            fprintf(arquivo, "Porcentagem de aprovados: %.2f\n", (statistics[i][4])*100);
        }

        fclose(arquivo);
    }

    FILE* file = fopen("estat.bin", "wb");
    for (int i = 0; i < (c - 1); i++){
        fwrite(statistics[i], sizeof(float), COLUNAS, file);
    }
    fclose(file);
}
