#include "main.h"

/*
This function will create the starting point of the tabou algorithm.
*/
int* buildFirstSolution(){
    int* solution = malloc (sizeof (int) * NBRDV);
    for (int i = 0; i < NBRDV; i++){
        solution[i] = (rand() % NBSOIG);
    }
    return solution;
}

/*
This function take a solution as arguement and will display it with it's parameter
*/
void printSolution(int solution[NBRDV]){
    for (int i = 0; i < NBRDV; i++){
        printf("%d",solution[i]);
    }
    return;
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
    if (argc != 6){
        printf("Veuillez suivre la syntaxe suivante : ./SESSAD directory range iteration intervenants missions\n"); //ANCHOR modify dir name
        return 1;
    }

    int range;
    if(sscanf(argv[2], "%d", &range) != 1) {
        printf("Range doit être un nombre entier \n");
        return 1;
    }

    int iter;
    if(sscanf(argv[3], "%d", &iter) != 1) {
        printf("Range doit être un nombre entier \n");
        return 1;
    }

    int intervenant;
    if(sscanf(argv[4], "%d", &intervenant) != 1) {
        printf("Intervenants doit être un nombre entier \n");
        return 1;
    }

    int missions;
    if(sscanf(argv[5], "%d", &missions) != 1) {
        printf("Missions doit être un nombre entier \n");
        return 1;
    }

    srand(time(0));
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            printf("%s",getPosition(j,i,"Intervenants.csv"));
        }
        printf("\n");
    }

    int array[32] = {2,0,1,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3};
    float buffer = computeScore(array,12.0,4);

    //lauching tabou
    /*int* solution = buildFirstSolution();
    tabouSearch(solution, range, solution, 0.0,iter,intervenant);*/
    return 0;
}