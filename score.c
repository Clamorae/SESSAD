#include "score.h"


float computeScore(int* solution,float bestScore, int intervenant){
    float newScore = 0.0;
    int tempsTravail[intervenant+1];
    float distance[intervenant+1], nonWorkmean,SDnonWork, diffWork[intervenant+1], overtime[intervenant+1], SDover;
    float mQuota=0.0, overtimeMean, distanceMean=0.0, SDdistance, overtimetot, distancetot;
    for (int i = 0; i < intervenant+1; i++){
        tempsTravail[i]=0;
    }
    
    int location = 0;
    for (int j = 0; j <32; j++){//ANCHOR fix number of mission (adaptability)
        tempsTravail[solution[j]] += atoi(getPosition(3,j,"Missions.csv")) - atoi(getPosition(2,j,"Missions.csv")); 
        float km = atof(getPosition(j+1,location,"Distances.csv"));
        tempsTravail[solution[j]] += (int)km*60/(50000);
        distance[solution[j]] += km;
        distancetot += km ;
    }

    for (int i = 0; i <intervenant ; i++){
        mQuota += atof(getPosition(3,i,"Intervenants.csv"));
    }
    mQuota = 100/ (mQuota / intervenant);

    for (int i = 1; i < intervenant+1; i++){
        diffWork[i] = atof(getPosition(3,i-1,"Intervenants.csv"))*60 - tempsTravail[i];
        if (diffWork[i]<0){
            overtime[i] = diffWork[i] * -1 ;
            overtimetot += overtime[i];
        }else{
            nonWorkmean += diffWork[i];
            overtime[i] = 0;
        }
    }
    nonWorkmean = nonWorkmean/(intervenant*60);
    overtimeMean = overtimetot/(intervenant*60);
    distanceMean = distancetot/(intervenant);

    SDnonWork = standardDeviation(intervenant,nonWorkmean,diffWork);
    SDover = standardDeviation(intervenant, overtimeMean, overtime);
    SDdistance = standardDeviation(intervenant, distanceMean, distance);
    printf("%f,   %f\n%f,   %f\n%f,   %f\n",nonWorkmean ,SDnonWork ,overtimeMean,SDover,distanceMean,SDdistance);
    
         
    newScore = (mQuota*SDnonWork+(100/overtimetot)*SDover+(100/distancetot)*SDdistance)/3;
    printf("%f\n",newScore);


    if (bestScore>newScore){
        return bestScore;
    }else{
        return newScore;
    }
    
}

float standardDeviation(int intervenant, float mean, float* data){
    float SD = 0;
    for (int i = 1; i < intervenant+1; i++) {
        SD += pow(data[i] - mean, 2);
    }
    return sqrt(SD / intervenant)/60;
}