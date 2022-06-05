OBJS	= main.o tabou.o score.o
SOURCE	= main.c tabou.c score.c
HEADER	= main.h tabou.h score.h
FLAGS	 = -g -c -Wall 

all: $(OBJS)
	$(CC)  $(OBJS) -o test -lm

main.o: main.c
	$(CC) $(FLAGS) main.c 

tabou.o: tabou.c
	$(CC) $(FLAGS) tabou.c 

score.o: score.c
	$(CC) $(FLAGS) score.c

clean:
	rm -f $(OBJS) $(OUT)

#clear: SESSAD.exe
#	rm score.o
#	rm tabou.o
#	rm main.o

#SESSAD.out: main.o tabou.o 
#	gcc -o SESSAD.exe main.o tabou.o score.o

#main.o: main.c
#	gcc -c main.c

#tabou.o: tabou.c
#	gcc -c tabou.c

#score.o: score.c
#	gcc -c score.c