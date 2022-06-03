#ifndef TABOU_H_  
#define TABOU_H_

#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "score.h"

#define NBRDV 10
#define NBSOIG 5

struct tabouItem{
    int* sol;
    struct tabouItem* next;
};

/*
This is the core of the tabou search where ... TODO
*/
void tabouSearch(int* solution, int iter, int intervenant, int missions);

/*
this function is gonna take a solution and build his neighbour then call a function to get the best one and check if it's the new best solution
*/
struct tabouItem* findBestNeighbor(int range, int* solution, int missions, int intervenant);

float isSolutionViable(int* solution, int missions, int intervenant);

#endif