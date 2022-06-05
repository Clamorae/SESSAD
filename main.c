#include "main.h"

/*
This function will create the starting point of the tabou algorithm.
*/
int* buildFirstSolution(int intervenant, int missions){
    int* solution = malloc (sizeof (int) * missions);
    int j = 1 ;
    for (int i = 0; i < missions; i++){
        solution[i] = j;
        if (j==intervenant){
            j=1;
        }else{
            j++;
        }
        printf("%d, ",solution[i]);
    }
    printf("\n");
    return solution;
}

void read_csv(int row, int col, char *filename, char ***data){
	FILE *file;
	file = fopen(filename, "r");

	int i = 0;
    char line[4098];
	while (fgets(line, 4098, file) && (i < row))
    {
    	// double row[ssParams->nreal + 1];
        char* tmp = strdup(line);
	    int j = 0;
	    const char* tok;
	    for (tok = strtok(line, ","); tok && *tok; j++, tok = strtok(NULL, ",")){
	        strcpy(data[i][j],tok);
	        printf("%s,", data[i][j]);
	    }
	    printf("\n");

        free(tmp);
        i++;
    }
}


int main(int argc, char *argv[]){
    
    //checking the base parameter
    if (argc != 5){
        printf("Veuillez suivre la syntaxe suivante : ./SESSAD directory iteration intervenants missions\n"); //ANCHOR modify dir name
        return 1;
    }

    int iter;
    if(sscanf(argv[2], "%d", &iter) != 1) {
        printf("Range doit être un nombre entier \n");
        return 1;
    }

    int intervenant;
    if(sscanf(argv[3], "%d", &intervenant) != 1) {
        printf("Intervenants doit être un nombre entier \n");
        return 1;
    }

    int missions;
    if(sscanf(argv[4], "%d", &missions) != 1) {
        printf("Missions doit être un nombre entier \n");
        return 1;
    }    

    char ***distancesCSV;
	distancesCSV = (char ***)malloc((missions+1) * sizeof(char **));
	for (int i = 0; i < (missions+1); ++i){
		distancesCSV[i] = (char **)malloc((missions+1)* sizeof(char*));
        for (int j =0; j < (missions+1); j++){
            distancesCSV[i][j] = (char *)malloc((missions+1) * sizeof(char));
        }
	}

    char ***intervenantCSV;
    intervenantCSV = (char ***)malloc(intervenant * sizeof(char **));
	for (int i = 0; i < intervenant; ++i){
		intervenantCSV[i] = (char **)malloc(4 * sizeof(char*));
        for (int j =0; j < 4; j++){
            intervenantCSV[i][j] = (char *)malloc(32 * sizeof(char));
        }
	}

    char ***missionCSV;
    missionCSV = (char ***)malloc(missions * sizeof(char **));
	for (int i = 0; i < missions; ++i){
		missionCSV[i] = (char **)malloc(6 * sizeof(char*));
        for (int j =0; j < 6; j++){
            missionCSV[i][j] = (char *)malloc(32 * sizeof(char));
        }
	}

    read_csv(missions+1,missions+1,"Instances/45-4/Distances.csv",distancesCSV);
    read_csv(intervenant,4,"Instances/45-4/Intervenants.csv",intervenantCSV);
    read_csv(missions,6,"Instances/45-4/Missions.csv",missionCSV);
    

    srand(time(0));

    int array[45] = {1,3,1,3,1,2,4,2,4,3,1,3,1,2,4,2,4,2,1,3,1,3,2,4,2,4,1,3,1,3,2,4,2,4,2,1,3,1,3,1,4,2,4,2,4};

    //lauching tabou
    //int* solution = buildFirstSolution(intervenant, missions);
    
    tabouSearch(array, iter, intervenant, missions, distancesCSV, missionCSV, intervenantCSV);
    //free(solution);
    for (int i = 0; i < missions+1; ++i){
        for (int j =0; j < missions+1; j++){
            free(distancesCSV[i][j]);
        }
        free(distancesCSV[i]);
	}
    free(distancesCSV);
	for (int i = 0; i < intervenant; ++i){
        for (int j =0; j < 4; j++){
            free(intervenantCSV[i][j]);
        }
        free(intervenantCSV[i]);
	}
    free(intervenantCSV);
    for (int i = 0; i < missions; ++i){
        for (int j =0; j < 6; j++){
            free(missionCSV[i][j]);
        }
        free(missionCSV[i]);
	}
    free(missionCSV);
    return 0;
}