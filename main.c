#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define NBRDV 10

bool isInArray(int solution[NBRDV], int num){
    for (int i = 0; i < NBRDV; i++){
        if (solution[i] == num){
            return true;
        }
    }
    return false;
}

int* buildFirstSolution(int nbSoignant){
    int* solution = malloc (sizeof (int) * NBRDV);
    int num;
    for (int i = 0; i < NBRDV; i++){
        solution[i] = (rand() % nbSoignant);
    }
    return solution;
}

void printSolution(int solution[NBRDV]){
    for (int i = 0; i < NBRDV; i++){
        printf("%d",solution[i]);
    }
    return;
}

void main(int argc, char *argv[]){
    srand(time(0));
    int nbSoignant =25;
    int* solution= buildFirstSolution(nbSoignant);
    printSolution(solution);
    return;
}