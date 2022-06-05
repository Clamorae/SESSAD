#include "score.h"


float computeFitnessEmployee(int* solution, int intervenant, int missions, char*** distancesCSV, char*** missionsCSV, char*** intervenantCSV){
    float newScore = 0.0;
    float tempsTravail[intervenant+1] ;
    float distance[intervenant+1], nonWorkmean,SDnonWork, diffWork[intervenant+1], overtime[intervenant+1], SDover;
    float mQuota=0.0, overtimeMean, distanceMean=0.0, SDdistance, overtimetot, distancetot;
    
    for (int i = 0; i < intervenant+1; i++){
        tempsTravail[i]=0.0;
    }

    int location = 0;
    for (int j = 0; j <missions; j++){
        tempsTravail[solution[j]] += atoi(missionsCSV[j][3]) - atoi(missionsCSV[j][2]);
        float km = atof(distancesCSV[location][j+1]);
        tempsTravail[solution[j]] += km*60/(50000);
        distance[solution[j]] += km;
        
        distancetot += km ;
        
    }//ANCHOR fusionne isViable et score    

    for (int i = 0; i <intervenant ; i++){
        mQuota += atof(intervenantCSV[i][3]);
    }
    mQuota = 100/ (mQuota / intervenant);

    for (int i = 1; i < intervenant+1; i++){
        diffWork[i] = atof(intervenantCSV[i-1][3])*60 - tempsTravail[i];
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
    SDover = standardDeviation(intervenant, overtimeMean, overtime);//TODO find why this cannot be equal to 0
    SDdistance = standardDeviation(intervenant, distanceMean, distance)/1000;
    float isOvertime;
    if (overtimetot==0.0){//avoid non possible solution 
        isOvertime=0.0;
    }else{
        isOvertime = SDover*(100/overtimetot);
    }
         
    float result = (mQuota*SDnonWork+isOvertime+(100/distancetot)*SDdistance)/3;
    printf("%f\n",result);
    return result;
}

float standardDeviation(int intervenant, float mean, float* data){
    float SD = 0;
    for (int i = 1; i < intervenant+1; i++) {
        SD += pow(data[i] - mean, 2);
    }
    return sqrt(SD / intervenant)/60;
}