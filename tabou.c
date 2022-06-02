#include "tabou.h"

int* tabouSearch(int* currentSolution, int range, int* bestSolution, float bestScore, int iteration, int intervenant){
    if (iteration==0){
        return bestSolution;
    }
    int* newBest = findBestNeighbour(currentSolution, bestSolution, bestScore, range, intervenant);

    //printf("%d\n",iteration);
    return tabouSearch(currentSolution,range,newBest,bestScore,iteration-1, intervenant);
}

int* findBestNeighbour(int* currentSolution, int* bestSolution, float bestScore, int range, int intervenant){
    int* buffer;
    float bufferScore;
    int j;
    for (int i = 0; i < range/2; i++){
        buffer = currentSolution;
        //printSolution(buffer);
        //ANCHOR IF time create function buffer creation
        
        if (buffer[sizeof(buffer)==NBSOIG]){
            j=0;
            do{
                buffer[sizeof(buffer)-j] = 0;
                j+=1;
            } while (buffer[sizeof(buffer)-j]==0);
            buffer[sizeof(buffer)-j]+=1;

        }else{
            buffer[sizeof(buffer)]+=i;
        } 
        
        bufferScore = computeScore(buffer,bestScore, intervenant);
        if(bufferScore>bestScore){
            bestSolution = buffer;
            bestScore=bufferScore;
        }


        if (buffer[sizeof(buffer)==0]){
            j=0;
            do{
                buffer[sizeof(buffer)-j] = NBSOIG;
                j+=1;
            } while (buffer[sizeof(buffer)-j]==0);
            buffer[sizeof(buffer)-j]-=1;     
        }else{
            buffer[sizeof(buffer)]+=i;
        } 

        bufferScore = computeScore(buffer,bestScore, intervenant);
        if(bufferScore>bestScore){
            bestSolution = buffer;
            bestScore=bufferScore;
        }

    }
    return  bestSolution;
}