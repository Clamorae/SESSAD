#ifndef MAIN_H_   
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "tabou.h"
#include "score.h"

#define NBRDV 10
#define NBSOIG 5


const char* getPosition(int x, int y,char* name);

const char* getfield(char* line, int num);

/*
This function will create the starting point of the taboul algorithm.
*/
int* buildFirstSolution();

/*
This function take a solution as arguement and will display it with it's parameter
*/
void printSolution(int solution[NBRDV]);

#endif 