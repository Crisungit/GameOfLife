# Makefile #

#Constants
CC = gcc
CFLAGS = -Wall -ansi -pedantic
SRCS = GameOfLife.c GameLogic.c BoardPrint.c
OBJECTS = $(SRCS:%.c=%.o)
ASSEMBLER = $(SRCS:%.c=%.s)
EXE = TheGame.exe
HEADER = GameOfLife.h
LIBS = -lncursesw

#Object compilation
%.o: %.c $(HEADER)
	$(CC) -c -g -o $@ $< $(CFLAGS)

#Assembler compilation 
%.s: %.c $(HEADER)
	$(CC) -S -o $@ $< $(CFLAGS)

#Lingking objects to .exe
$(EXE): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

#Clean the targets .o and .s files
clean:
	del -f *.o *.s TheGame.exe

#All targets
all: $(EXE) $(ASSEMBLER)

#Assembler target
assembler: $(ASSEMBLER)