#include "main.h"
#include "tabou.h"

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

const char* getfield(char* line, int num)
{
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

const char* getPosition(int x, int y){
    int i = 0;
    x++;
    FILE* stream = fopen("./Instances/45-4/Intervenants.csv", "r");//ANCHOR remplacer par file en parmaetre
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
        printf("%s\n",getPosition(0,i));
    }
    

    //lauching tabou
    int* solution = buildFirstSolution();
    tabouSearch(solution, range, solution, 0.0,iter);
    return 0;
}