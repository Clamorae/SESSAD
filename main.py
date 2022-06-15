import pandas as pd
import numpy as np
import random as rd
import time

intervenants = 10
missions = 100
sizePop = 80
timeout = time.time() + 60 * 1

intervenantsCSV = pd.read_csv("./Instances/100-10/Intervenants.csv", header=None)
missionsCSV = pd.read_csv("./Instances/100-10/Missions.csv", header=None)
distancesCSV = pd.read_csv("./Instances/100-10/Distances.csv", header=None)




#-----------------GET_LINE----------------------------------------------------------------------------------
#This function will decide which solution is used for the next generation
#It will take the population's size as parameter return a number (the choosen line)
#the higher the ranking of the solution, the more likely it is to be selected
#-----------------GET_LINE----------------------------------------------------------------------------------

def get_line(sizePop):
    sizeSum = (sizePop+1)*(0+sizePop)//2
    parent = rd.randrange(0,sizeSum)
    for i in range(sizePop):
        parent = parent - (sizePop -i)
        if parent <= 0 :
            return i

#-----------------GENETIC----------------------------------------------------------------------------------
# Here is created the new generation using two different breeding method
# There is one mutation per child as the aim is to explore as much solutions as possible in a certain time
#-----------------GENETIC----------------------------------------------------------------------------------

def genetic(solutions,missions,sizePop):
    newGeneration = np.empty((sizePop,missions))

    for i in range(sizePop//4):
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
    
    return newGeneration
        
#-----------------COMPUTE_SCORE----------------------------------------------------------------------------------
# The first of the three computation function and the bigger, in this one each solution validity is checked for each
# non-respected constraint a malus is given. Then the malus is added to the evaluation of the function, using this
# solution which does not respect the constraint will have a very bad score.
#-----------------COMPUTE_SCORE----------------------------------------------------------------------------------
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
    k = 0.0

    
    for i in range (missions):

        # check for the competences' affectation 
        if intervenantsCSV.values[int(solution[i])][1] != missionsCSV.values[i][4]:
            score+= 999.9
        
        
        if firstDailyMission[int(solution[i])]!=0:
            #adding the travel and the travelTime since the last mission
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
                        score += 99.9
            
            #check for the mission superposition
            elif (int(missionsCSV.values[i][1]) == int(missionsCSV.values[int(lastMission[int(solution[i])])][1] ) ) and ((int(missionsCSV.values[i][2]) - (int(missionsCSV.values[int(lastMission[int(solution[i])])][3])))<0):
                    score += 999.9 

            distanceIntervenant[int(solution[i])] += distance
            lastMission[int(solution[i])]=i
            
        #creating the first mission of the day
        else:
            distance = float(distancesCSV.values[0][i+1])/1000
            distanceIntervenant[int(solution[i])] += distance
            tempsTrajet = distance*60/50
            firstDailyMission[int(solution[i])]=i
            lastMission[int(solution[i])]=i
        
        k+=float(distancesCSV.values[0][i+1])/1000
        k+=float(distancesCSV.values[i+1][0])/1000
        dailyWorkTime[int(solution[i])][int(missionsCSV.values[i][1])-1] += tempsTrajet + float(missionsCSV.values[i][3]) - float(missionsCSV.values[i][2])
        

    for i in range (intervenants):
        #checking the daily overtime
        for j in range(5):
            if (dailyWorkTime[i][j] > 360 and int(intervenantsCSV.values[i][3])==24) or (dailyWorkTime[i][j] > 480 and int(intervenantsCSV.values[i][3])==35):
                score+=99.9
            totWork[i]+=dailyWorkTime[i][j]

        if int(intervenantsCSV[3][i])*60 - totWork[i] > 0:
            nonWorktime[i] = int(intervenantsCSV[3][i])*60 - totWork[i]
        else:
            overtime[i] = int(intervenantsCSV[3][i])*60 - totWork[i]

        #checking the weekly overtime
        if totWork[i] > int(intervenantsCSV.values[i][3])*60 + 600:
            score +=99.9
        
        quotaMean += float(intervenantsCSV.values[i][3])*60
        distancetot += distanceIntervenant[i]
    
    #calculating the fitness
    quotaMean = quotaMean / intervenants
                  
    SDnonWork = np.std(nonWorktime)
    SDovertime = np.std(overtime)
    SDdistance = np.std(distanceIntervenant)
    score += ((100/quotaMean)*SDnonWork + (100/10*intervenants)*SDovertime + (100/(k/intervenants))*SDdistance)/3

    return score



#-----------------COMPUTE_SECOND----------------------------------------------------------------------------------
# The second fitness computation is shorter than the first, it will only check if the specialities are corresponding
#-----------------COMPUTE_SECOND----------------------------------------------------------------------------------

def compute_second(missions, solutions, missionsCSV, intervernantsCSV):
    result = np.zeros(10)
    for i in range(len(solutions)):
        penalities = 0
        for j in range(missions):
            if missionsCSV[5][j] != intervenantsCSV[2][int(solutions[i][j])]:
                penalities += 1
        result[i] = (100/missions)*penalities
    return result

#-----------------COMPUTE_THIRD----------------------------------------------------------------------------------
# The third evaluation is measuring the working's time equality for everyone# 
#-----------------COMPUTE_THIRD----------------------------------------------------------------------------------

def compute_third(solution, missions, intervenants, intervenantsCSV, missionsCSV, distancesCSV):
    lastMission = np.zeros(intervenants)
    dailyWorkTime = np.zeros((intervenants,5))
    totWork = np.zeros(intervenants)
    k = 0.0
    distancetot = 0.0
    distanceMax = 0.0

    for i in range (missions):        
        distance = float(distancesCSV.values[int(lastMission[int(solution[i])])+1][i+1])/1000
        k+=float(distancesCSV.values[0][i+1])/1000
        k+=float(distancesCSV.values[i+1][0])/1000
        distancetot += distance
        if distance > distanceMax :
            distanceMax = distance
        lastMission[int(solution[i])]=i
        tempsTrajet = distance*60/50
        dailyWorkTime[int(solution[i])][int(missionsCSV.values[i][1])-1] += tempsTrajet + float(missionsCSV.values[i][3]) - float(missionsCSV.values[i][2])

    sumWOH = 0.0
    for i in range (intervenants):
        for j in range(5):
            totWork[i]+=dailyWorkTime[i][j]
        sumWOH = abs(int(intervenantsCSV[3][i])*60 - totWork[i])

    result = ((100/45)*sumWOH + (100/(k/intervenants))*(distancetot/intervenants) + (100/(k/intervenants))*distanceMax) /3
    
    return result



#-----------------SHOW_SCORE-----------------------------------------------------------------------------------------
# A function printing information about the last solution this one is called at the very end of the programm
#-----------------SHOW_SCORE-----------------------------------------------------------------------------------------

def show_score(solution, missions, intervenants, intervenantsCSV, missionsCSV, distancesCSV):
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
    k = 0.0

    
    for i in range (missions):
      
        
        if firstDailyMission[int(solution[i])]!=0:
            #adding the travel and the travelTime since the last mission
            distance = float(distancesCSV.values[int(lastMission[int(solution[i])])+1][i+1])/1000
            tempsTrajet = distance*60/50

            if missionsCSV.values[int(firstDailyMission[int(solution[i])])][1]!=missionsCSV.values[i][1]:
                firstDailyMission[int(solution[i])]=i

            distanceIntervenant[int(solution[i])] += distance
            lastMission[int(solution[i])]=i
            
        #creating the first mission of the day
        else:
            distance = float(distancesCSV.values[0][i+1])/1000
            distanceIntervenant[int(solution[i])] += distance
            tempsTrajet = distance*60/50
            firstDailyMission[int(solution[i])]=i
            lastMission[int(solution[i])]=i
        
        k+=float(distancesCSV.values[0][i+1])/1000
        k+=float(distancesCSV.values[i+1][0])/1000
        dailyWorkTime[int(solution[i])][int(missionsCSV.values[i][1])-1] += tempsTrajet + float(missionsCSV.values[i][3]) - float(missionsCSV.values[i][2])
        

    for i in range (intervenants):
        #checking the daily overtime
        for j in range(5):
            totWork[i]+=dailyWorkTime[i][j]

        if int(intervenantsCSV[3][i])*60 - totWork[i] > 0:
            nonWorktime[i] = int(intervenantsCSV[3][i])*60 - totWork[i]
        else:
            overtime[i] = int(intervenantsCSV[3][i])*60 - totWork[i]
        
        quotaMean += float(intervenantsCSV.values[i][3])*60
        distancetot += distanceIntervenant[i]
    
    #calculating the fitness
    quotaMean = quotaMean / intervenants
                  
    SDnonWork = np.std(nonWorktime)
    SDovertime = np.std(overtime)
    SDdistance = np.std(distanceIntervenant)
    score += ((100/quotaMean)*SDnonWork + (100/10*intervenants)*SDovertime + (100/(k/intervenants))*SDdistance)/3
    
    #print an overview of the solutions 
    distancetot = 0.0
    overtimetot =0.0
    NWTot =0.0
    for i in range(intervenants):
        distancetot += distanceIntervenant[i]
        overtimetot += overtime[i]
        NWTot += nonWorktime[i]
    print("distance :",distancetot)
    print("overtime :",overtimetot)
    print("wasted time :",NWTot)

    return score


#-----------------MAIN-----------------------------------------------------------------------------------------
# The main is the core of the program, here are created the first solution, called the genetic function,
# generating the solution shape and sorting them
#-----------------MAIN-----------------------------------------------------------------------------------------

#Initialisation of the useful array 
solutions  = np.zeros((sizePop,missions))
solScore = np.zeros(sizePop)
bestsol =  np.zeros((sizePop,missions))
bestsolScore= np.full(sizePop, 99999.9)
buffer = np.zeros(missions)


#creation of height good solution and sizePop-n random solution for more diversity
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


#get the score of the initial population
for i in range (sizePop):
    solScore[i] = compute_score(solutions[i],missions,intervenants, intervenantsCSV, missionsCSV, distancesCSV)

#sorting the initial population (bubble sort)
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


#adding new solutions in the array of the best solution
for i in range(sizePop):
    isAlready=False
    for j in range(sizePop):
        if bestsolScore[j] == solScore[i]:
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
    #creation of the nex generation using genetic()
    solutions = genetic(solutions,missions,sizePop)
    
    #evaluation of the new generation
    for i in range (sizePop):
        solScore[i] = compute_score(solutions[i],missions,intervenants, intervenantsCSV, missionsCSV, distancesCSV)
    
    #sorting the initial popilation (bubble sort)
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

    #adding new solutions in the array of the best solution
    for i in range(sizePop):
        isAlready=False
        for j in range(sizePop):
            if bestsolScore[j] == solScore[i]:
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
    
    #stop the generation of new population when a certain amout of time has passed
    if time.time()>timeout :
        break

#creation of another array with the ten best solution 
secondSol = np.zeros((10,missions))
for i in range(10):
    secondSol[i] = bestsol[sizePop - 1 -i].copy()

#computing the solution's score by the second criteria
secondScore = compute_second(missions, secondSol,missionsCSV, intervenantsCSV)

#sorting the second array (bubble sort)
for i in range(10):
    swapped = False
    for j in range(0, 10-i-1):
        if secondScore[j] > secondScore[j+1] :
            secondScore[j], secondScore[j+1] = secondScore[j+1], secondScore[j]
            buffer = secondSol[j+1].copy()
            secondSol[j+1] = secondSol[j].copy()
            secondSol[j] = buffer.copy()
            swapped = True
    if swapped == False:
        break

#generation of a new array with the five best solution
#then evaluation of these solution and the best one is choosen
thirdSol = np.zeros((5,missions))
bestthird = 9999.9
for i in range(5):
    thirdSol[i] = secondSol[i].copy()
    newthird = compute_third(thirdSol[i],missions,intervenants,intervenantsCSV,missionsCSV,distancesCSV)
    if newthird < bestthird :
        bestthird = newthird
        choosenSol = i

print("La meilleure solution trouvée est:")
print(thirdSol[choosenSol])
print("score de la première équation : ",show_score(thirdSol[choosenSol],missions,intervenants,intervenantsCSV,missionsCSV,distancesCSV))