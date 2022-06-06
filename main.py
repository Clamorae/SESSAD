from telnetlib import DO
import pandas as pd
import numpy as np
import random as rd

intervenants = 4
missions = 45

def genetic(solutions,missions):
    newGeneration = np.empty((20,missions))

    for i in range(5):
        a = 4*i
        b = (4*i) + 1
        c = (4*i) + 2
        d = (4*i) + 3
        print(a,b,c,d)
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
        
    for i in range (20):
        print("[", end = '')
        for j in range (missions):
            print(newGeneration[i,j],",", end = '')
        print("],")

#-----------------MAIN-----------------------------------------------------------------------------------------
solutions  = np.empty((20,missions))
for i in range (20):
    print("[", end = '')
    for j in range (missions):
        solutions[i,j] = rd.randrange(0,intervenants)
        print(solutions[i,j],",", end = '')
    print("],")
solutions = genetic(solutions,missions)


