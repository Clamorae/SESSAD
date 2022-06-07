from faulthandler import disable
import pandas as pd
import numpy as np
import random as rd
import time

intervenants = 4
missions = 45
sizePop = 40
timeout = time.time() + 60 * 1

intervenantsCSV = pd.read_csv("./Instances/45-4/Intervenants.csv", header=None)
missionsCSV = pd.read_csv("./Instances/45-4/Missions.csv", header=None)
distancesCSV = pd.read_csv("./Instances/45-4/Distances.csv", header=None)

#-----------------get_line----------------------------------------------------------------------------------
def get_line(sizePop):
    sizeSum = (sizePop+1)*(0+sizePop)//2
    parent = rd.randrange(0,sizeSum)
    for i in range(sizePop):
        parent = parent - (sizePop -i)
        if parent <= 0 :
            return i

#-----------------genetic----------------------------------------------------------------------------------
def genetic(solutions,missions,sizePop):
    newGeneration = np.empty((sizePop,missions))

    for i in range(10):#adapt this
        a = 4*i
        b = (4*i) + 1
        c = (4*i) + 2
        d = (4*i) + 3
        e = get_line(sizePop)
        f = get_line(sizePop)
        while e==f:
            f = get_line(sizePop)
        g = get_line(sizePop)
        h = get_line(sizePop)
        while g==h:
            h = get_line(sizePop)
        #order crossover
        x = rd.randrange(1,missions-1)
        y = rd.randrange(1,missions-1)

        while x==y:
            y = rd.randrange(1,missions-1)

        if x > y:
            for i in range(0,y):
                newGeneration[a,i] = solutions[e,i]
                newGeneration[b,i] = solutions[f,i]
            for i in range(y,x):
                newGeneration[b,i] = solutions[e,i]
                newGeneration[a,i] = solutions[f,i]
            for i in range(x,missions):
                newGeneration[a,i] = solutions[e,i]
                newGeneration[b,i] = solutions[f,i]

        else:
            for i in range(0,x):
                newGeneration[a,i] = solutions[e,i]
                newGeneration[b,i] = solutions[f,i]
            for i in range(x,y):
                newGeneration[b,i] = solutions[e,i]
                newGeneration[a,i] = solutions[f,i]
            for i in range(y,missions):
                newGeneration[a,i] = solutions[e,i]
                newGeneration[b,i] = solutions[f,i]
        

        #Uniform crossover
        bMask = np.empty(missions)
        for i in bMask:
            i = rd.randrange(0,1)
        for i in range(missions):
            if bMask[i]==0:
                newGeneration[c,i] = solutions[g,i]
                newGeneration[d,i] = solutions[h,i]
            else:
                newGeneration[d,i] = solutions[g,i]
                newGeneration[c,i] = solutions[h,i]
        
        #mutations
        newGeneration[a,rd.randrange(0,missions)] == rd.randrange(0,3)
        newGeneration[b,rd.randrange(0,missions)] == rd.randrange(0,3) 
        newGeneration[c,rd.randrange(0,missions)] == rd.randrange(0,3)
        newGeneration[d,rd.randrange(0,missions)] == rd.randrange(0,3)
    
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
                    score+= 99.9
                firstDailyMission[int(solution[i])]=i

            #check for the lunch time    
            
            elif int(missionsCSV.values[i][2])> 720 and int(missionsCSV.values[i][2]) < 840:
                if int(missionsCSV.values[i][2]) - int(missionsCSV.values[int(lastMission[int(solution[i])])][3]<60):
                    if  int(missionsCSV.values[int(lastMission[int(solution[i])])][3]) > 720 and int(missionsCSV.values[int(lastMission[int(solution[i])])][3])<840:
                        print("lunch")
                        score += 99.9
            
            elif (int(missionsCSV.values[i][1]) == int(missionsCSV.values[int(lastMission[int(solution[i])])][1] ) ) and ((int(missionsCSV.values[i][2]) - (int(missionsCSV.values[int(lastMission[int(solution[i])])][3])))<0):
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
                score+=99.9
            totWork[i]+=dailyWorkTime[i][j]

        if int(intervenantsCSV[3][i])*60 - totWork[i] > 0:
            nonWorktime[i] = int(intervenantsCSV[3][i])*60 - totWork[i]
        else:
            overtime[i] = int(intervenantsCSV[3][i])*60 - totWork[i]

        if totWork[i] > int(intervenantsCSV.values[i][3])*60 + 600:
            score +=99.9
        
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
buffer = np.zeros(missions)

for i in range (sizePop):
    if i < intervenants:    
        inter = i
        for j in range(missions):
            if missionsCSV.values[j][4] == intervenantsCSV.values[inter][1]:
                solutions[i,j] = inter
            else:
                while missionsCSV.values[j][4] != intervenantsCSV.values[inter][1]:
                    if inter < intervenants-1:
                        inter += 1
                    else:
                        inter = 0
                solutions[i,j] = inter
            if inter < intervenants-1:
                inter += 1
            else:
                inter = 0 
    elif i < 2*intervenants:
        inter = i - intervenants
        for j in range(missions):
            if missionsCSV.values[j][4] == intervenantsCSV.values[inter][1]:
                solutions[i,j] = inter
            else:
                while missionsCSV.values[j][4] != intervenantsCSV.values[inter][1]:
                    if inter > 0:
                        inter -= 1
                    else:
                        inter = intervenants -1
                solutions[i,j] = inter
            if inter > 0:
                inter -= 1
            else:
                inter = intervenants -1
    else:
        for j in range (missions):
            solutions[i,j] = rd.randrange(0,intervenants)
for i in range (sizePop):
        solScore[i] = compute_score(solutions[i],missions,intervenants, intervenantsCSV, missionsCSV, distancesCSV)

for i in range(sizePop):
    swapped = False
    for j in range(0, sizePop-i-1):
        if solScore[j] > solScore[j+1] :
            solScore[j], solScore[j+1] = solScore[j+1], solScore[j]
            buffer = solutions[j+1].copy()
            solutions[j+1] = solutions[j].copy()
            solutions[j] = buffer.copy()
            swapped = True
    if swapped == False:
        break


isAlready=False
for i in range(sizePop):
    for j in range(sizePop):
        if np.array_equal(bestsol[j],solutions[i]):
            isAlready = True
    if isAlready == False:
        
        if solScore[i] < bestsolScore[0]:
            
            bestsolScore[0] = solScore[i]
            bestsol[0] = solutions[i]
            for j in range(sizePop-1):
                if bestsolScore[j] < bestsolScore[j+1]:
                    bestsolScore[j], bestsolScore[j+1] = bestsolScore[j+1], bestsolScore[j]
                    buffer = bestsol[j+1].copy()
                    bestsol[j+1] = bestsol[j].copy()
                    bestsol[j] = buffer.copy()
                else :
                    j=sizePop
        else :
            i=sizePop


while True:
    
    solutions = genetic(solutions,missions,sizePop)
    
    for i in range (sizePop):
        solScore[i] = compute_score(solutions[i],missions,intervenants, intervenantsCSV, missionsCSV, distancesCSV)
    
    #bubble sort
    
    for i in range(sizePop):
        swapped = False
        for j in range(0, sizePop-i-1):
            if solScore[j] > solScore[j+1] :
                solScore[j], solScore[j+1] = solScore[j+1], solScore[j]
                buffer = solutions[j+1].copy()
                solutions[j+1] = solutions[j].copy()
                solutions[j] = buffer.copy()
                swapped = True
        if swapped == False:
            break

    isAlready=False
    for i in range(sizePop):
        for j in range(sizePop):
            if np.array_equal(bestsol[j],solutions[i]):
                isAlready = True
        if isAlready == False:
            if solScore[i] < bestsolScore[0]:
                bestsolScore[0] = solScore[i]
                bestsol[0] = solutions[i]
                for j in range(sizePop-1):
                    if bestsolScore[j] < bestsolScore[j+1]:
                        bestsolScore[j], bestsolScore[j+1] = bestsolScore[j+1], bestsolScore[j]
                        buffer = bestsol[j+1].copy()
                        bestsol[j+1] = bestsol[j].copy()
                        bestsol[j] = buffer.copy()
                    else :
                        j=sizePop
            else :
                i=sizePop
    
    if time.time()>timeout :
        break

print(bestsolScore)

arr =[1,3,1,3,1,0,2,0,2,3,1,3,1,0,2,0,2,0,1,3,1,3,0,2,0,2,1,3,1,3,0,2,0,2,0,1,3,1,3,1,2,0,2,0,2]
arrzer =[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
testscore = compute_score(arr, missions, intervenants, intervenantsCSV,missionsCSV,distancesCSV)
testzer = compute_score(arrzer, missions, intervenants, intervenantsCSV,missionsCSV,distancesCSV)
print(testscore)


#TODO final comput
#TODO better breeding