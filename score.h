#ifndef SCORE_H_  
#define SCORE_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "tabou.h"

/*
    this function will take the solution and build it's fitness
*/
float computeScore(int* solution,float bestScore, int intervenant);

#endif