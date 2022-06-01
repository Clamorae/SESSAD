#OBJS	= main.o tabou.o
#SOURCE	= main.c tabou.c
#HEADER	= main.h tabou.h
#FLAGS	 = -g -c -Wall

#all: $(OBJS)
#	$(CC) -g $(OBJS) -o test

#main.o: main.c
#	$(CC) $(FLAGS) main.c 

#tabou.o: tabou.c
#	$(CC) $(FLAGS) tabou.c 


#clean:
#	rm -f $(OBJS) $(OUT)
clear: SESSAD.exe
	rm tabou.o
	rm main.o

SESSAD.out: main.o tabou.o 
	gcc -o SESSAD.exe main.o tabou.o 

main.o: main.c
	gcc -c main.c

tabou.o: tabou.c
	gcc -c tabou.c
