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
float computeFitnessEmployee(int* solution, int intervenant, char*** distancesCSV, char*** missionsCSV, char*** intervenantCSV);

float standardDeviation(int intervenant, float mean, float* data);

#endif