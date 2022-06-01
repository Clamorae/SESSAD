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

int main(int argc, char *argv[]){
    if (argc != 4){
        printf("Veuillez suivre la syntaxe suivante : ./SESSAD file range iteration\n"); //ANCHOR modify when everything is up
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
    srand(time(0));
    int* solution = buildFirstSolution();
    tabouSearch(solution, range, solution, 0.0,iter);
    return 0;
}