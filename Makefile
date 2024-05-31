.PHONY: all run

CC = gcc
CCFLAGS = -lm 
SRC = ranNum.c
BUILD = r
SKEL = main.c

all:
	$(CC) $(SRC) $(SKEL) -o $(BUILD) $(CCFLAGS)

run:
	./$(BUILD)
