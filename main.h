#ifndef MAIN_H_   
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "tabou.h"
#include "score.h"

const char* getPosition(int x, int y,char* name);

const char* getfield(char* line, int num);

/*
This function will create the starting point of the taboul algorithm.
*/
int* buildFirstSolution(int intervenant, int mission);


#endif 