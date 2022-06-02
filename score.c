#include "score.h"


float computeScore(int* solution,float bestScore, int intervenant){
    float newScore = 0.0;
    int tempsTravail[intervenant];
    for (int i = 0; i < intervenant; i++){
        tempsTravail[i]=0;
    }
    
    int location = 0;
        for (int j = 0; j <sizeof(solution); j++){
            tempsTravail[solution[j]] += atoi(getPosition(3,j,"Missions.csv")) - atoi(getPosition(2,j,"Missions.csv")); 
            float km = atof(getPosition(j+1,location,"Distances.csv"));
            tempsTravail[solution[j]] += (int)km*60/(50000);
        }





    if (bestScore>newScore){
        return bestScore;
    }else{
        return newScore;
    }
    
}