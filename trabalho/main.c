/* Alunos:
Gabriel Alves Hussein   17/0103200
Victor Amaral Cerqueira 17/0164411
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definicoes Gerais
typedef int item;
#define key(A) (A)
#define less(A,B) (key(A) < key(B))
#define exch(A,B) {item t=A; A=B, B=t;}
#define cmpexch(A,B) {if(less(B,A)) exch(A,B);}

typedef struct Materia{
    char nome[100];
    int horarioInicio;
    int horarioFim;
    int creditos;
}MATERIA;

// Chamada das Funcoes
void mostraMenu(int totalMaterias);
void ordena(MATERIA *v, int l, int r);
void merge(MATERIA *v, int l, int r1, int r2);
void cadastroMateria (MATERIA *materia, int totalMaterias);
int selecionarMateria (MATERIA *materia, MATERIA *materiaCadastrada, int totalMaterias, int ultimoIndice);
void ordenarHorario(MATERIA *materiaCadastrada, int totalMaterias, int materiasSelecionadas);

int main(){
    MATERIA materia[100];
    MATERIA materiaCadastrada[16];
    int totalMaterias = 0, opcao, materiasSelecionadas = 0;

    do{
        mostraMenu(totalMaterias);
        scanf("%d",&opcao);
        system("clear");
        switch(opcao){
        case 1:
            cadastroMateria(materia, totalMaterias);
            totalMaterias++;
            getc(stdin);
            printf("Aperte enter para voltar ao menu.");
            break;
        case 2:
            materiasSelecionadas = selecionarMateria(materia, materiaCadastrada, totalMaterias, materiasSelecionadas);
            getc(stdin);
            break;
        case 3:
            ordena(materiaCadastrada, 0, materiasSelecionadas-1);
            ordenarHorario(materiaCadastrada, totalMaterias, materiasSelecionadas);
            break;
        }
  }while(opcao != 0);

    return 0;
}

// Desenvolvimento das funcoes 
void mostraMenu(int totalMaterias){
  printf("\n");
  printf(" ====================================================\n");
  printf("|             >>>>>>>>> Menu <<<<<<<<<               |\n");
  printf("| 1 - Adicionar Materia (%d materias cadastradas)     |\n", totalMaterias);
  printf("| 2 - Selecionar Materias para grade                 |\n");
  printf("| 3 - Gerar grade horaria                            |\n");
  printf("| 0 - Sair                                           |\n");
  printf(" ====================================================\n");
  printf("Sua opcao: ");
}

void ordena(MATERIA *v, int l, int r){
    if(l>=r) return;
    int meio = (r+l)/2;
    ordena(v, l, meio);
    ordena(v, meio+1, r);
    merge(v, l, meio, r);
}

void merge(MATERIA *v, int l, int r1, int r2){
    MATERIA v2[16];
    int k = 0;
    int i = l;
    int j = r1 + 1;

    while (i <= r1 && j <= r2)
    {
        if (less(v[i].horarioFim, v[j].horarioFim))
            v2[k++] = v[i++];
        else
            v2[k++] = v[j++];
    }

    while (i <= r1)
        v2[k++] = v[i++];
    while (j <= r2)
        v2[k++] = v[j++];

    k = 0;
    for (int i = l; i <= r2; i++)
    {
        v[i] = v2[k++];
    }

    return;
}

void cadastroMateria (MATERIA *materia, int totalMaterias) {
    printf("Digite o nome da materia a ser cadastrada: \n");
    scanf(" %[^\n]s", materia[totalMaterias].nome);
    
    printf("Digite o Horario de inicio da materia a ser cadastrada: \n");
    scanf("%d", &materia[totalMaterias].horarioInicio);
    
    printf("Digite o numero de creditos da materia a ser cadastrada: \n");
    scanf("%d", &materia[totalMaterias].creditos);

    materia[totalMaterias].horarioFim = materia[totalMaterias].horarioInicio + 2;
}

int selecionarMateria(MATERIA *materia, MATERIA *materiaCadastrada, int totalMaterias, int ultimoIndice){
    int codigo;
    
    for(int j = 0; j < totalMaterias; j++){
        printf("Codigo: %d\nNome: %s\nHorario: %d - %d\nCreditos: %d\n\n", j+1, materia[j].nome, materia[j].horarioInicio, materia[j].horarioFim, materia[j].creditos);
    }

    printf("Selecione uma materia disponivel(Selecione o codigo): \n");
    scanf("%d", &codigo);
    
    for(int i = 0; i <= ultimoIndice; i++){
        if(strcmp(materia[codigo-1].nome, materiaCadastrada[i].nome) == 0){
            printf("Materia ja selecionada, favor selecionar outra.\n");
            return ultimoIndice;
        }
    }
    
    materiaCadastrada[ultimoIndice] = materia[codigo-1];
    ultimoIndice = ultimoIndice + 1;
    return ultimoIndice;
}

void ordenarHorario(MATERIA *materiaCadastrada, int totalMaterias, int materiasSelecionadas){
    MATERIA gradeHoraria[16];
    MATERIA ultimaMateria;
    
    int totalMateriaCadastrada = 0;
    int nCreditos = 0;
    for(int i = 0; i < materiasSelecionadas; i++){
        if(i==0){
            nCreditos += materiaCadastrada[i].creditos;
            gradeHoraria[totalMateriaCadastrada] = materiaCadastrada[i];
            ultimaMateria = gradeHoraria[totalMateriaCadastrada];
            totalMateriaCadastrada++;
        }
        
        if(materiaCadastrada[i].horarioInicio >= ultimaMateria.horarioFim && i>0){
            if(nCreditos + materiaCadastrada[i].creditos <= 32){
                gradeHoraria[totalMateriaCadastrada] = materiaCadastrada[i];
                totalMateriaCadastrada++;
                nCreditos += materiaCadastrada[i].creditos;
            }
        }
    }

    printf("Grade horaria mais eficiente disponivel:\n");
    for(int z = 0; z < totalMateriaCadastrada; z++){
        printf("Nome: %s\nHorario: %d - %d\nCreditos: %d\n\n", gradeHoraria[z].nome, gradeHoraria[z].horarioInicio, gradeHoraria[z].horarioFim, gradeHoraria[z].creditos);
    }   
    printf("Total de creditos neste semestre: %d\n", nCreditos);
}