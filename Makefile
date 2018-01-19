TARGET = create
CC = gcc
CFLAGS = -Wall -g -std=gnu11
INCLUDES = -Iinclude
LIBS = -lGLEW -lGLU -lGL -lglut -lm
SRC = $(wildcard source/*.c)

default: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) $(wildcard lib/*.a) $(INCLUDES) $(LIBS) -o $(TARGET)

clean:
	rm $(TARGET)
