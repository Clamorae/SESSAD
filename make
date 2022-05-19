OBJS	= main.o tabou.o
SOURCE	= main.c tabou.c
HEADER	= main.h tabou.h
FLAGS	 = -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c 

tabou.o: tabou.c
	$(CC) $(FLAGS) tabou.c 


clean:
	rm -f $(OBJS) $(OUT)
