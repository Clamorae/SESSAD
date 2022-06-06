from traceback import print_tb
import pandas as pd
import numpy as np
import random as rd

intervenants = 4
missions = 45
intervenantsCSV = pd.read_csv("./Instances/45-4/Intervenants.csv", header=None)
missionsCSV = pd.read_csv("./Instances/45-4/Missions.csv", header=None)
distancesCSV = pd.read_csv("./Instances/45-4/Distances.csv", header=None)


#-----------------genetic----------------------------------------------------------------------------------
def genetic(solutions,missions):
    newGeneration = np.empty((20,missions))

    for i in range(5):
        a = 4*i
        b = (4*i) + 1
        c = (4*i) + 2
        d = (4*i) + 3
        #order crossover
        x = rd.randrange(1,missions-1)
        y = rd.randrange(1,missions-1)

        while x==y:
            y = rd.randrange(1,missions-1)

        if x > y:
            for i in range(0,y):
                newGeneration[a,i] = solutions[a,i]
                newGeneration[b,i] = solutions[b,i]
            for i in range(y,x):
                newGeneration[b,i] = solutions[a,i]
                newGeneration[a,i] = solutions[b,i]
            for i in range(x,missions):
                newGeneration[a,i] = solutions[a,i]
                newGeneration[b,i] = solutions[b,i]

        else:
            for i in range(0,x):
                newGeneration[a,i] = solutions[a,i]
                newGeneration[b,i] = solutions[b,i]
            for i in range(x,y):
                newGeneration[b,i] = solutions[a,i]
                newGeneration[a,i] = solutions[b,i]
            for i in range(y,missions):
                newGeneration[a,i] = solutions[a,i]
                newGeneration[b,i] = solutions[b,i]
    

        #Uniform crossover
        bMask = np.empty(missions)
        for i in bMask:
            i = rd.randrange(0,1)
        for i in range(missions):
            if bMask[i]==0:
                newGeneration[c,i] = solutions[c,i]
                newGeneration[d,i] = solutions[d,i]
            else:
                newGeneration[d,i] = solutions[c,i]
                newGeneration[c,i] = solutions[d,i]
    
    #ANCHOR maybe more mutation type
    return newGeneration
        
   
#-----------------compute_score----------------------------------------------------------------------------------
def compute_score(solution, missions, intervenants, intervenantsCSV, missionsCSV, distancesCSV):
    score = 0.0
    firstDailyMission = np.zeros(intervenants)
    lastMission = np.zeros(intervenants)
    dailyWorkTime = np.zeros((intervenants,5))
    totWork = np.zeros(intervenants)

    
    for i in range (missions):
        # check for the competences affectation 
        if intervenantsCSV.values[int(solution[i])][1] != missionsCSV.values[i][4]:
            score+= 999.9
        
        # check if there is less than 12h between the first and the last mission
        if firstDailyMission[int(solution[i])]!=0:
            if missionsCSV.values[int(firstDailyMission[int(solution[i])])][1]!=missionsCSV.values[i][1]:
                if missionsCSV.values[int(lastMission[int(solution[i])])][1] - missionsCSV.values[int(firstDailyMission[int(solution[i])])][1] >720:
                    score+= 999.9
                firstDailyMission[int(solution[i])]=i
        else:
            firstDailyMission[int(solution[i])]=i
            lastMission[int(solution[i])]=i
        
        dailyWorkTime[int(solution[i])][int(missionsCSV.values[i][1])-1] += int(missionsCSV.values[i][3]) - int(missionsCSV.values[i][2])

    for i in range (intervenants):
        for j in range(5):
            if (dailyWorkTime[i][j] > 360 and int(intervenantsCSV.values[i][3])==24) or (dailyWorkTime[i][j] > 480 and int(intervenantsCSV.values[i][3])==35):
                score+=999.9
            totWork[i]+=dailyWorkTime[i][j]

        if totWork[i] > int(intervenantsCSV.values[i][3])*60 + 600:
            score +=999.9
                  


    return score

#-----------------MAIN-----------------------------------------------------------------------------------------
solutions  = np.zeros((20,missions))
solScore = np.zeros(20)
for i in range (20):
#    print("[", end = '')
    for j in range (missions):
        solutions[i,j] = rd.randrange(0,intervenants)
#        print(solutions[i,j],",", end = '')
#    print("],")

solutions = genetic(solutions,missions)
for i in range (20):
    solScore[i] = compute_score(solutions[i],missions,intervenants, intervenantsCSV, missionsCSV, distancesCSV)
print(solScore)


#TODO finir contrainte + score
#TODO loop sur newgen
#TODO mutation
#TODO final comput