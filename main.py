from traceback import print_tb
import pandas as pd
import numpy as np
import random as rd

intervenants = 4
missions = 45
sizePop = 20
intervenantsCSV = pd.read_csv("./Instances/45-4/Intervenants.csv", header=None)
missionsCSV = pd.read_csv("./Instances/45-4/Missions.csv", header=None)
distancesCSV = pd.read_csv("./Instances/45-4/Distances.csv", header=None)


#-----------------genetic----------------------------------------------------------------------------------
def genetic(solutions,missions):
    newGeneration = np.empty((sizePop,missions))

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
    
    #ANCHOR maybe more breeding type
    return newGeneration
        
   
#-----------------compute_score----------------------------------------------------------------------------------
def compute_score(solution, missions, intervenants, intervenantsCSV, missionsCSV, distancesCSV):
    score = 0.0
    firstDailyMission = np.zeros(intervenants)
    lastMission = np.zeros(intervenants)
    dailyWorkTime = np.zeros((intervenants,5))
    nonWorktime = np.zeros(intervenants)
    overtime = np.zeros(intervenants)
    totWork = np.zeros(intervenants)
    distanceIntervenant = np.zeros(intervenants)
    distancetot = 0.0
    quotaMean = 0.0

    
    for i in range (missions):
        # check for the competences affectation 
        if intervenantsCSV.values[int(solution[i])][1] != missionsCSV.values[i][4]:
            score+= 999.9
        
        
        if firstDailyMission[int(solution[i])]!=0:
            distance = float(distancesCSV.values[int(lastMission[int(solution[i])])+1][i+1])/1000
            tempsTrajet = distance*60/50

            if missionsCSV.values[int(firstDailyMission[int(solution[i])])][1]!=missionsCSV.values[i][1]:
                # check if there is less than 12h between the first and the last mission
                if missionsCSV.values[int(lastMission[int(solution[i])])][1] - missionsCSV.values[int(firstDailyMission[int(solution[i])])][1] >720:
                    score+= 999.9
                firstDailyMission[int(solution[i])]=i

            #check for the lunch time    
            elif int(missionsCSV.values[i][2])> 720 and int(missionsCSV.values[i][2]) < 840:
                if int(missionsCSV.values[i][2]) - int(missionsCSV.values[int(lastMission[int(solution[i])])][3]<60):
                    score += 999.9

            elif int(missionsCSV.values[i][2]) - (int(missionsCSV.values[int(lastMission[int(solution[i])])][3] + tempsTrajet)<0):
                    score += 999.9 
            distanceIntervenant[int(solution[i])] += distance
            lastMission[int(solution[i])]=i
            
        else:
            distance = float(distancesCSV.values[0][i+1])/1000
            distanceIntervenant[int(solution[i])] += distance
            tempsTrajet = distance*60/50
            firstDailyMission[int(solution[i])]=i
            lastMission[int(solution[i])]=i
        
        dailyWorkTime[int(solution[i])][int(missionsCSV.values[i][1])-1] += tempsTrajet + float(missionsCSV.values[i][3]) - float(missionsCSV.values[i][2])
        

    for i in range (intervenants):
        for j in range(5):
            if (dailyWorkTime[i][j] > 360 and int(intervenantsCSV.values[i][3])==24) or (dailyWorkTime[i][j] > 480 and int(intervenantsCSV.values[i][3])==35):
                score+=999.9
            totWork[i]+=dailyWorkTime[i][j]

        if int(intervenantsCSV[3][i])*60 - totWork[i] > 0:
            nonWorktime[i] = int(intervenantsCSV[3][i])*60 - totWork[i]
        else:
            overtime[i] = int(intervenantsCSV[3][i])*60 - totWork[i]

        if totWork[i] > int(intervenantsCSV.values[i][3])*60 + 600:
            score +=999.9
        
        quotaMean += float(intervenantsCSV.values[i][3])*60
        distancetot += distanceIntervenant[i]
    
    quotaMean = quotaMean / intervenants
                  
    SDnonWork = np.std(nonWorktime)
    SDovertime = np.std(overtime)
    SDdistance = np.std(distanceIntervenant)
    score += ((100/quotaMean)*SDnonWork + (100/10*intervenants)*SDovertime + (100/distancetot)*SDdistance)/3

    return score

#-----------------MAIN-----------------------------------------------------------------------------------------
solutions  = np.zeros((sizePop,missions))
solScore = np.zeros(sizePop)
bestsol =  np.zeros((sizePop,missions))
bestsolScore= np.full(sizePop, 99999.9)

for i in range (sizePop):
#    print("[", end = '')
    for j in range (missions):
        solutions[i,j] = rd.randrange(0,intervenants)
#        print(solutions[i,j],",", end = '')
#    print("],")

solutions = genetic(solutions,missions)
for i in range (sizePop):
    solScore[i] = compute_score(solutions[i],missions,intervenants, intervenantsCSV, missionsCSV, distancesCSV)

#bubble sort
for i in range(sizePop-1):
    for j in range(sizePop -1 -i):
        if solScore[j] > solScore[j+1]:
            solScore[j], solScore[j+1] = solScore[j+1], solScore[j]
            solutions[j], solutions[j+1] = solutions[j+1], solutions[j]

for i in range(sizePop):
    if solScore[i] < bestsolScore[0]:
        bestsolScore[0] = solScore[i]
        bestsol[0] = solutions[i]
        
        for j in range(sizePop-1):
            if bestsolScore[j] < bestsolScore[j+1]:
                bestsolScore[j], bestsolScore[j+1] = bestsolScore[j+1], bestsolScore[j]
                bestsol[j], bestsol[j+1] = bestsol[j+1], bestsol[j]
            else :
                j=sizePop
    else :
        i=sizePop

print(solScore)
print(bestsolScore)


#TODO loop sur newgen
#TODO mutation
#TODO final comput