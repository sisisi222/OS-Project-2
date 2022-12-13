OBJS	= memsim.o myPage.o utils.o
SOURCE	= memsim.cpp myPage.c utils.c
HEADER	= myPage.h utils.h
OUT	= memsim
CC	 = g++
FLAGS	 = -g -c -std=c++17
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

memsim.o: memsim.cpp
	$(CC) $(FLAGS) memsim.cpp 

myPage.o: myPage.c
	$(CC) $(FLAGS) myPage.c 

utils.o: utils.c
	$(CC) $(FLAGS) utils.c 


clean:
	rm -f $(OBJS) $(OUT)
