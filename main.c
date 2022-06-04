#include "main.h"

/*
This function will create the starting point of the tabou algorithm.
*/
int* buildFirstSolution(int intervenant, int missions){
    int* solution = malloc (sizeof (int) * missions);
    int j = 1 ;
    for (int i = 0; i < missions; i++){
        solution[i] = j;
        if (j==intervenant){
            j=1;
        }else{
            j++;
        }
        printf("%d, ",solution[i]);
    }
    printf("\n");
    return solution;
}

const char* getfield(char* line, int num){
    const char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

const char* getPosition(int x, int y,char* name){
    int i = 0;
    char path[64];
    strcpy(path,"./Instances/45-4/");
    strcat(path,name);
    x++;
    FILE* stream = fopen(path, "r");//ANCHOR remplacer par file en parmaetre
    char line[1024];
    while (fgets(line, 1024, stream)){
        char* tmp = strdup(line);
        if (i==y){
            return getfield(tmp, x);
        }
        i++;
        free(tmp);
    }
}


int main(int argc, char *argv[]){
    
    //checking the base parameter
    if (argc != 5){
        printf("Veuillez suivre la syntaxe suivante : ./SESSAD directory iteration intervenants missions\n"); //ANCHOR modify dir name
        return 1;
    }

    int iter;
    if(sscanf(argv[2], "%d", &iter) != 1) {
        printf("Range doit être un nombre entier \n");
        return 1;
    }

    int intervenant;
    if(sscanf(argv[3], "%d", &intervenant) != 1) {
        printf("Intervenants doit être un nombre entier \n");
        return 1;
    }

    int missions;
    if(sscanf(argv[4], "%d", &missions) != 1) {
        printf("Missions doit être un nombre entier \n");
        return 1;
    }

    srand(time(0));

    int array[45] = {1,3,1,3,1,2,4,2,4,3,1,3,1,2,4,2,4,2,1,3,1,3,2,4,2,4,1,3,1,3,2,4,2,4,2,1,3,1,3,1,4,2,4,2,1};

    //lauching tabou
    //int* solution = buildFirstSolution(intervenant, missions);
    
    tabouSearch(array, iter, intervenant, missions);
    //free(solution);
    return 0;
}