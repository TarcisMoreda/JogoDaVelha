CC:=gcc
SRCS:=$(wildcard ./src/*.c)

all:
	$(CC) $(SRCS) -o JogoDaVelha.bin -lraylib