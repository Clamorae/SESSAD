#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "main.h"
#include "tabou.h"

#define NBRDV 10
#define NBSOIG 5

/*
This function will create the starting point of the taboul algorithm.
*/
int* buildFirstSolution(int NBSOIG){
    int* solution = malloc (sizeof (int) * NBRDV);
    int num;
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

void main(int argc, char *argv[]){
    if (argc != 3){
        printf("Veuillez suivre la syntaxe suivante : ./SESSAD file range") //ANCHOR modify when everything is up
        return;
    }
    
    srand(time(0));
    int* solution = buildFirstSolution(NBSOIG);
    tabouSearch(solution, range);
    return;
}