#include "tabou.h"

void tabouSearch(int *solution, int iter, int intervenant, int missions, char ***distancesCSV, char ***missionCSV, char ***intervenantCSV)
{
    int tabouSize = 20;
    int range = 5;
    struct tabouItem *tabouHead = (struct tabouItem *)malloc(sizeof(struct tabouItem));
    struct tabouItem *tabouBuffer = (struct tabouItem *)malloc(sizeof(struct tabouItem));
    tabouHead->sol = solution;
    tabouHead->score = 200.0;
    for (int i = 0; i < iter; i++)
    {
        if (i < tabouSize)
        {
            if (i == 0)
            {
                tabouHead->next = findBestNeighbor(range, tabouHead->sol, missions, intervenant, distancesCSV, missionCSV, intervenantCSV);
            }
            else if (i < tabouSize)
            {
                tabouBuffer = tabouHead->next;
                for (int j = 0; j < i - 1; i++)
                {
                    tabouBuffer = tabouBuffer->next;
                }
                tabouBuffer->next = findBestNeighbor(range, tabouBuffer->sol, missions, intervenant, distancesCSV, missionCSV, intervenantCSV);
            }
            else
            {
                tabouHead = tabouHead->next;
                tabouBuffer = tabouHead;
                free(tabouBuffer);
                for (int i = 0; i < tabouSize - 1; i++)
                {
                    tabouBuffer = tabouBuffer->next;
                }
                tabouBuffer->next = findBestNeighbor(range, tabouBuffer->sol, missions, intervenant, distancesCSV, missionCSV, intervenantCSV);
            }
        }
    }
}

struct tabouItem *findBestNeighbor(int range, int *solution, int missions, int intervenant, char ***distancesCSV, char ***missionCSV, char ***intervenantCSV)
{
    int *solcpy = (int *)malloc(sizeof(int) * missions);
    memcpy(solcpy, solution, sizeof(int) * missions);
    int *bestNeighbour = (int *)malloc(sizeof(int) * missions);
    float bestScore = 200.0, newScore = 0.0, malus;
    int x;
    for (int i = 0; i < range; i++)
    {//ANCHOR si suivant correspond pas à comp delete direct
        if (solcpy[missions - 1] >= intervenant)
        {
            x = 0;
            while (solcpy[missions - 1 - x] == intervenant && missions - 1 - x != 0)
            {
                solcpy[missions - 1 - x] = 0;
                x++;
            }
            if ((missions - 1 - x) == 0)
            {
                solcpy[0] = 0;
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

        /*for (int j = 0; j < missions; j++)
        {
            printf("%d, ", solcpy[j]);
        }
        printf("\n");*/

        malus = isSolutionViable(solcpy, missions, intervenant, distancesCSV, missionCSV, intervenantCSV);
        if (malus < 200)
        {
            //newScore = computeFitnessEmployee(solution, intervenant, distancesCSV, missionCSV, intervenantCSV);
            if (newScore + malus > bestScore)
            {
                bestScore = newScore;
                memcpy(bestNeighbour, solcpy, sizeof(int) * missions);
            }
        }
        else
        {
            range += 1;
        }
    }
    struct tabouItem *best = (struct tabouItem *)malloc(sizeof(struct tabouItem));
    best->score = bestScore;
    memcpy(best->sol ,bestNeighbour, sizeof(int) * missions);
    printf("zarma\n");
    // TODO neg solcpy
    free(solcpy);
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

    for (int i = 0; i < missions; i++)
    {
        // non affecté
        if (solution[i] == 0)
        {
            malus += 5.0;
        }
        // mauvaise comp
        if (strcmp(missionsCSV[4][i], intervenantCSV[1][solution[i]]) != 0)
        {
            return 200.0;
        }
        if (lastMission[solution[i]] != 0)
        {
            // superposition horaire

            if (0 > (atof(missionsCSV[2][i]) - (atof(missionsCSV[3][lastMission[solution[i]]])) + (atof(distancesCSV[lastMission[solution[i]]][i]) * 60 / (50000))))
                {
                    return 200.0;
                }
            // si jour différent
            if (atoi(missionsCSV[1][lastMission[solution[i]]]) != atoi(missionsCSV[1][i]))
            {
                printf("in\n");
                // amplitude horaire
                if ((atoi(missionsCSV[3][lastMission[solution[i]]]) - atoi(missionsCSV[2][lastMission[solution[i]]])) > 720)
                {
                    return 200.0;
                }
                // heure max plein temps
                if (workTime[solution[i]] > 480)
                {
                    return 200.0;
                }
                // heure max mi-temps
                if (24 == atoi(intervenantCSV[3][solution[i]]) && workTime[solution[i]] > 360)
                {
                    return 200.0;
                }
                firstMission[solution[i]] = i;
            }
        }
        else
        {
            printf("out\n");
            firstMission[solution[i]] = i;
        }
        workTime[solution[i]] += (atoi(missionsCSV[3][lastMission[solution[i]]]) - atoi(missionsCSV[2][lastMission[solution[i]]]));
        // ANCHOR ajouter trajet à worktime
        lastMission[solution[i]] = i;

        // TODO 1h de pause entre 12 et 14h
    }
    return malus;
}