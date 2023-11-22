PROG_NAME = labMonteCarlo
CC = gcc
CC_FLAGS = -O3 -march=native -mavx

all: $(PROG_NAME)

$(PROG_NAME): labMonteCarlo.o utils.o
	$(CC) $(CC_FLAGS) -o $(PROG_NAME) labMonteCarlo.o utils.o -lm

labMonteCarlo.o: labMonteCarlo.c
	$(CC) $(CC_FLAGS) -c labMonteCarlo.c -lm

utils.o: utils.c utils.h
	$(CC) $(CC_FLAGS) -c utils.c -lm

clean:
	rm -f *.o $(PROG_NAME)

test: $(PROG_NAME)
	./$(PROG_NAME) 0 1 10000000 2 > 2dim.txt
	./$(PROG_NAME) 1 1 10000000 4 > 4dim.txt
	./$(PROG_NAME) 2 1 10000000 8 > 8dim.txt