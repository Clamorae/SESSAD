#include <stdio.h>
                  
#define NBR_INTERFACES        24
#define NBR_APPRENANTS        80
#define NBR_FORMATIONS        80
#define NBR_CENTRES_FORMATION 5
#define NBR_SPECIALITES       5
#define NBR_NODES 	      NBR_CENTRES_FORMATION+NBR_INTERFACES+NBR_APPRENANTS
                  
/* code des compétence en langage des signes et en codage LPC */
#define COMPETENCE_SIGNES     0
#define COMPETENCE_CODAGE     1
                  
/* competences des interfaces en SIGNES et CODAGE*/
int competences_interfaces[NBR_INTERFACES][2]={
    {1,0}, /* compétence en langages des SIGNES mais pas en CODAGE LPC */
    {0,1}, /* pas de compétence en langages des SIGNES mais compétence en CODAGE LPC */
    {0,1},
    {1,0},
    {0,1},
    {1,0},
    {0,1},
    {0,1},
    {0,1},
    {0,1},
    {1,0},
    {0,1},
    {0,1},
    {1,0},
    {1,0},
    {1,0},
    {1,0},
    {0,1},
    {0,1},
    {1,1},
    {1,0},
    {1,0},
    {1,0},
    {1,0}
};
                  
/* spécialités des interfaces */
#define SPECIALITE_SANS       -1 /* Enseigné dans le centre le plus proche */
#define SPECIALITE_MENUISERIE 0
#define SPECIALITE_ELECTRICITE 1
#define SPECIALITE_MECANIQUE 2
#define SPECIALITE_INFORMATIQUE 3
#define SPECIALITE_CUISINE 4
                  
/* specialite des interfaces */
int specialite_interfaces[NBR_INTERFACES][NBR_SPECIALITES]={
    {1,0,1,1,0},
    {0,0,0,1,1},
    {0,1,1,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,1,0,0,0},
    {0,1,0,0,0},
    {0,0,0,1,1},
    {1,0,0,0,0},
    {0,0,0,0,1},
    {0,1,1,0,1},
    {0,0,0,1,0},
    {0,0,0,0,0},
    {1,0,0,0,0},
    {0,0,1,1,0},
    {0,0,0,0,0},
    {0,0,1,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,1},
    {1,0,1,0,1},
    {0,0,0,0,0},
    {1,0,0,0,0}
};
                  
/* coordonnées des centres de formation, des interfaces et des apprenants */
float coord[NBR_NODES][2]={
                  
    /* Les interfaces se rendent du centre SESSAD à l'école de formation */
    {154,163}, /* centre 0 */
                  
    /* Centres de formation */
    {129,54}, /* ecole formation SPECIALITE_MENUISERIE */
    {132,138}, /* ecole formation SPECIALITE_ELECTRICITE */
    {38,199}, /* ecole formation SPECIALITE_MECANIQUE */
    {189,35}, /* ecole formation SPECIALITE_INFORMATIQUE */
    {67,107}, /* ecole formation SPECIALITE_CUISINE */
                  
    /* Apprenants */
    {173,2}, /* apprenant 0 */
    {84,139}, /* apprenant 1 */
    {109,188}, /* apprenant 2 */
    {42,8}, /* apprenant 3 */
    {188,110}, /* apprenant 4 */
    {76,187}, /* apprenant 5 */
    {150,75}, /* apprenant 6 */
    {35,154}, /* apprenant 7 */
    {79,132}, /* apprenant 8 */
    {18,46}, /* apprenant 9 */
    {122,72}, /* apprenant 10 */
    {5,52}, /* apprenant 11 */
    {17,126}, /* apprenant 12 */
    {86,50}, /* apprenant 13 */
    {71,70}, /* apprenant 14 */
    {29,176}, /* apprenant 15 */
    {145,197}, /* apprenant 16 */
    {77,181}, /* apprenant 17 */
    {69,75}, /* apprenant 18 */
    {177,32}, /* apprenant 19 */
    {111,177}, /* apprenant 20 */
    {138,14}, /* apprenant 21 */
    {148,156}, /* apprenant 22 */
    {29,172}, /* apprenant 23 */
    {59,91}, /* apprenant 24 */
    {119,162}, /* apprenant 25 */
    {21,143}, /* apprenant 26 */
    {16,177}, /* apprenant 27 */
    {164,37}, /* apprenant 28 */
    {148,48}, /* apprenant 29 */
    {113,93}, /* apprenant 30 */
    {193,38}, /* apprenant 31 */
    {44,123}, /* apprenant 32 */
    {74,79}, /* apprenant 33 */
    {46,33}, /* apprenant 34 */
    {116,52}, /* apprenant 35 */
    {22,187}, /* apprenant 36 */
    {63,147}, /* apprenant 37 */
    {195,100}, /* apprenant 38 */
    {157,180}, /* apprenant 39 */
    {87,65}, /* apprenant 40 */
    {112,41}, /* apprenant 41 */
    {162,77}, /* apprenant 42 */
    {0,58}, /* apprenant 43 */
    {16,4}, /* apprenant 44 */
    {42,179}, /* apprenant 45 */
    {86,167}, /* apprenant 46 */
    {160,126}, /* apprenant 47 */
    {2,106}, /* apprenant 48 */
    {57,154}, /* apprenant 49 */
    {137,75}, /* apprenant 50 */
    {184,169}, /* apprenant 51 */
    {170,98}, /* apprenant 52 */
    {121,7}, /* apprenant 53 */
    {7,158}, /* apprenant 54 */
    {61,20}, /* apprenant 55 */
    {4,4}, /* apprenant 56 */
    {134,7}, /* apprenant 57 */
    {48,20}, /* apprenant 58 */
    {197,25}, /* apprenant 59 */
    {180,118}, /* apprenant 60 */
    {70,172}, /* apprenant 61 */
    {175,186}, /* apprenant 62 */
    {190,127}, /* apprenant 63 */
    {120,157}, /* apprenant 64 */
    {152,186}, /* apprenant 65 */
    {79,156}, /* apprenant 66 */
    {69,60}, /* apprenant 67 */
    {72,101}, /* apprenant 68 */
    {132,59}, /* apprenant 69 */
    {168,172}, /* apprenant 70 */
    {103,17}, /* apprenant 71 */
    {122,74}, /* apprenant 72 */
    {34,100}, /* apprenant 73 */
    {82,71}, /* apprenant 74 */
    {182,177}, /* apprenant 75 */
    {40,95}, /* apprenant 76 */
    {159,18}, /* apprenant 77 */
    {97,95}, /* apprenant 78 */
    {147,156}/* apprenant 79 */
};
                  
#define NBR_FORMATION          80
                  
#define LUNDI                  1
#define MARDI                  2
#define MERCREDI               3
#define JEUDI                  4
#define VENDREDI               5
#define SAMEDI                 6
                  
/* formation : id formation, specialite ou centre de formation, competence, horaire debut formation, horaire fin formation */
int formation[NBR_FORMATION][6]={
   {0,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,SAMEDI,16,18},
   {1,SPECIALITE_CUISINE,COMPETENCE_SIGNES,SAMEDI,9,11},
   {2,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MARDI,10,12},
   {3,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,JEUDI,16,19},
   {4,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,SAMEDI,15,18},
   {5,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,9,11},
   {6,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MARDI,9,12},
   {7,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,14,17},
   {8,SPECIALITE_CUISINE,COMPETENCE_SIGNES,VENDREDI,14,17},
   {9,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,JEUDI,10,12},
   {10,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MARDI,13,17},
   {11,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,SAMEDI,16,19},
   {12,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,14,19},
   {13,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MERCREDI,9,11},
   {14,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,15,17},
   {15,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MERCREDI,14,18},
   {16,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,VENDREDI,15,17},
   {17,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,15,19},
   {18,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,14,16},
   {19,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,VENDREDI,9,11},
   {20,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,SAMEDI,15,18},
   {21,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,VENDREDI,13,15},
   {22,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MERCREDI,14,19},
   {23,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,MARDI,14,19},
   {24,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MERCREDI,8,12},
   {25,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,JEUDI,15,17},
   {26,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,10,12},
   {27,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MERCREDI,8,12},
   {28,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,SAMEDI,10,12},
   {29,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,SAMEDI,13,19},
   {30,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,LUNDI,8,11},
   {31,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MARDI,15,18},
   {32,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,JEUDI,9,12},
   {33,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,VENDREDI,9,12},
   {34,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,JEUDI,10,12},
   {35,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,LUNDI,10,12},
   {36,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,8,12},
   {37,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,JEUDI,10,12},
   {38,SPECIALITE_CUISINE,COMPETENCE_CODAGE,VENDREDI,10,12},
   {39,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,15,17},
   {40,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,VENDREDI,9,12},
   {41,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,LUNDI,15,18},
   {42,SPECIALITE_CUISINE,COMPETENCE_CODAGE,MARDI,9,12},
   {43,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,LUNDI,9,12},
   {44,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,VENDREDI,9,12},
   {45,SPECIALITE_CUISINE,COMPETENCE_SIGNES,MERCREDI,9,12},
   {46,SPECIALITE_INFORMATIQUE,COMPETENCE_CODAGE,MARDI,15,19},
   {47,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,8,12},
   {48,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,SAMEDI,14,17},
   {49,SPECIALITE_CUISINE,COMPETENCE_SIGNES,MERCREDI,10,12},
   {50,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,SAMEDI,13,18},
   {51,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,SAMEDI,13,18},
   {52,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,10,12},
   {53,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,JEUDI,9,11},
   {54,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,15,17},
   {55,SPECIALITE_CUISINE,COMPETENCE_CODAGE,LUNDI,13,17},
   {56,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,8,11},
   {57,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,SAMEDI,10,12},
   {58,SPECIALITE_CUISINE,COMPETENCE_CODAGE,JEUDI,8,10},
   {59,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,JEUDI,16,19},
   {60,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,SAMEDI,16,19},
   {61,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,JEUDI,15,17},
   {62,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MERCREDI,16,18},
   {63,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,SAMEDI,13,18},
   {64,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,VENDREDI,15,18},
   {65,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,VENDREDI,15,19},
   {66,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,16,19},
   {67,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,MARDI,14,18},
   {68,SPECIALITE_INFORMATIQUE,COMPETENCE_SIGNES,SAMEDI,16,19},
   {69,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,LUNDI,9,12},
   {70,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,13,19},
   {71,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,LUNDI,8,11},
   {72,SPECIALITE_CUISINE,COMPETENCE_SIGNES,LUNDI,15,19},
   {73,SPECIALITE_CUISINE,COMPETENCE_SIGNES,SAMEDI,15,18},
   {74,SPECIALITE_CUISINE,COMPETENCE_SIGNES,MERCREDI,8,10},
   {75,SPECIALITE_CUISINE,COMPETENCE_SIGNES,VENDREDI,10,12},
   {76,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MARDI,16,18},
   {77,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,8,10},
   {78,SPECIALITE_CUISINE,COMPETENCE_SIGNES,SAMEDI,8,12},
   {79,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,LUNDI,16,19}
};
                  
int main() {
                  
    printf("NBR_INTERFACES=%d\n",NBR_INTERFACES) ;
    printf("NBR_APPRENANTS=%d\n",NBR_APPRENANTS) ;
    printf("NBR_FORMATIONS=%d\n",NBR_FORMATIONS) ;
    printf("NBR_NODES=%d\n",NBR_NODES) ;
                  
    return 0 ;
}
                  
