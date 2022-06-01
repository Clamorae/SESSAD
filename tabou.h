#ifndef TABOU_H_  
#define TABOU_H_

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#define NBRDV 10
#define NBSOIG 5

/*
This is the core of the tabou search where ... TODO
*/
int* tabouSearch(int* currentSolution, int range, int* bestSolution, float bestScore, int iteration);

/*
this function is gonna take a solution and build his neighbour then call a function to get the best one and check if it's the new best solution
*/
int* findBestNeighbour(int* currentSolution, int* bestSolution, float bestScore, int range);

/*
    this function will take the solution and build it's fitness
*/
float computeScore(int* solution,float bestScore);

#endif