#include "tabou.h"

void tabouSearch(int *solution, int iter, int intervenant, int missions, char ***distancesCSV, char ***missionCSV, char ***intervenantCSV)
{
    int tabouSize = 20;
    int range = 100;
    struct tabouItem *tabouHead = (struct tabouItem *)malloc(sizeof(struct tabouItem));
    struct tabouItem *tabouBuffer = (struct tabouItem *)malloc(sizeof(struct tabouItem));
    struct tabouItem *tabouClear = (struct tabouItem *)malloc(sizeof(struct tabouItem));
    int** finalSol = (int**)malloc(sizeof(int*)*10);
    for (int i = 0; i < 10; ++i){
		finalSol[i] = (int*)malloc(missions* sizeof(int));
    } 
    float finalScore[10];
    for (int i = 0; i < 9; i++)
    {
        finalScore[i] = 99999.0;
    }
    tabouHead->sol = solution; 
    tabouHead->score = isSolutionViable(solution,missions,intervenant,distancesCSV,missionCSV,intervenantCSV);// + computeFitnessEmployee(solution,intervenant,missions,distancesCSV,missionCSV,intervenantCSV);
    finalScore[9] = tabouHead->score;
    memcpy(finalSol[9],solution,sizeof(int)*missions);
    for (int i = 0; i < iter; i++)
    {

        printf("%d/%d", i, iter );
        printf("\n");
            if (i == 0)
            {
                tabouHead->next = findBestNeighbor(range, tabouHead->sol, missions, intervenant, distancesCSV, missionCSV, intervenantCSV);
                tabouBuffer = tabouHead->next;
                printf("\n\n%d\n",tabouBuffer->sol[0]);
            }
            else if (i < tabouSize)
            {
                
                tabouBuffer->next = findBestNeighbor(range, tabouBuffer->sol, missions, intervenant, distancesCSV, missionCSV, intervenantCSV);
                tabouBuffer = tabouBuffer->next;
            }
            else
            {
                tabouClear = tabouHead;
                tabouHead = tabouHead->next;
                free(tabouClear);
                tabouBuffer->next = findBestNeighbor(range, tabouBuffer->sol, missions, intervenant, distancesCSV, missionCSV, intervenantCSV);
                tabouBuffer = tabouBuffer->next;
            }
        if(tabouBuffer->score<finalScore[0]){
            finalScore[0] = tabouBuffer->score;
            memcpy(finalSol[0],tabouBuffer->sol,sizeof(int)*missions);
            for (int j = 1; j < 10; j++)
            {
                if(tabouBuffer->score<finalScore[j]){
                    finalScore[j-1]=finalScore[j];
                    memcpy(finalSol[j-1],finalSol[j],sizeof(int)*missions);
                    finalScore[j] = tabouBuffer->score;
                    memcpy(finalSol[j],tabouBuffer->sol,sizeof(int)*missions);
                }else{
                    j=10;
                }
            }            
        }
    }
    printf("bestsol are :\n");
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < missions; j++){
            printf("%d, ",finalSol[i][j]);
        }
        printf(": %f\n",finalScore[i]);
    }
    
}

struct tabouItem* findBestNeighbor(int range, int *solution, int missions, int intervenant, char ***distancesCSV, char ***missionCSV, char ***intervenantCSV)
{
    int *solcpy = (int *)malloc(sizeof(int) * missions);
    memcpy(solcpy, solution, sizeof(int) * missions);
    int *bestNeighbour = (int *)malloc(sizeof(int) * missions);
    float bestScore = 9999.0, newScore = 0.0, malus;
    int x;
    for (int i = 0; i < range; i++)
    {//ANCHOR si suivant correspond pas à comp delete direct
            if (solcpy[missions - 1] >= intervenant)
            {
                x = 0;
                while (solcpy[missions - 1 - x] == intervenant && missions - 1 - x != 0)
                {
                    solcpy[missions - 1 - x] = 1;
                    x++;
                }
                if ((missions - 1 - x) == 0)
                {
                    solcpy[0] = 1;
                }
                else
                {
                    solcpy[missions - 1 - x] += 1;
                }
            }
            else
            {
                solcpy[missions - 1] += 1;
            }
        
            for (int j = 0; j < missions; j++){
                printf("%d, ",solcpy[j]);
            }
            printf("\n");
        

        malus = isSolutionViable(solcpy, missions, intervenant, distancesCSV, missionCSV, intervenantCSV);
        newScore = computeFitnessEmployee(solcpy, intervenant, missions,distancesCSV, missionCSV, intervenantCSV);
        if (newScore + malus < bestScore||(i==range-1 && bestScore==9999.0))
        {

            bestScore = newScore+malus;
            memcpy(bestNeighbour, solcpy, sizeof(int) * missions);
        }
    }
    
    struct tabouItem *best = (struct tabouItem *)malloc(sizeof(struct tabouItem));
    best->score = bestScore;
    best->sol = bestNeighbour;
    // TODO neg solcpy
    return best;
}

float isSolutionViable(int *solution, int missions, int intervenant, char ***distancesCSV, char ***missionsCSV, char ***intervenantCSV)
{
    float malus = 0.0;
    int lastMission[intervenant];
    int firstMission[intervenant];
    int workTime[intervenant];
    for (int i = 0; i < intervenant; i++)
    {
        lastMission[i] = 0;
        firstMission[i] = 0;
        workTime[i] = 0;
    }

    return malus;
} 
    /*for (int i = 0; i < intervenant; i++)
    {
        lastMission[i] = 0;
        firstMission[i] = 0;
        workTime[i] = 0;
    }

    for (int i = 0; i < missions; i++)
    {
        printf("%d\n",i);
        // non affecté
        if (solution[i] == 0)
        {
            malus += 5.0;
        }
        // mauvaise comp
        if (strcmp(missionsCSV[4][i], intervenantCSV[1][solution[i]]) != 0)
        {
            malus +=5000.0;
        }
        if (lastMission[solution[i]] != 0)
        {
            // superposition horaire

            if (0 > (atof(missionsCSV[2][i]) - (atof(missionsCSV[3][lastMission[solution[i]]])) + (atof(distancesCSV[lastMission[solution[i]]][i]) * 60 / (50000))))
                {
                    malus+= 5000.0;
                }
            // si jour différent
            if (atoi(missionsCSV[1][lastMission[solution[i]]]) != atoi(missionsCSV[1][i]))
            {
                // amplitude horaire
                if ((atoi(missionsCSV[3][lastMission[solution[i]]]) - atoi(missionsCSV[2][lastMission[solution[i]]])) > 720)
                {
                    malus+= 200.0;
                }
                // heure max plein temps
                if (workTime[solution[i]] > 480)
                {
                    malus+= 200.0;
                }
                // heure max mi-temps
                if (24 == atoi(intervenantCSV[3][solution[i]]) && workTime[solution[i]] > 360)
                {
                    malus+= 200.0;
                }
                firstMission[solution[i]] = i;
            }
        }
        else
        {
            firstMission[solution[i]] = i;
        }
        workTime[solution[i]] += (atoi(missionsCSV[3][lastMission[solution[i]]]) - atoi(missionsCSV[2][lastMission[solution[i]]]));
        // ANCHOR ajouter trajet à worktime
        lastMission[solution[i]] = i;

        // TODO 1h de pause entre 12 et 14h
    }
    return malus;
}*/