TARGET = create
CC = gcc
CFLAGS = -Wall -g -std=c11 
INCLUDES = -Iinclude 
LIBS = -lGL -lGLU -lglut -lGLEW -lm
SRC = $(wildcard source/*.c)

default: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) $(wildcard lib/*.a) $(INCLUDES) $(LIBS) -o $(TARGET)

clean:
	rm $(TARGET)

