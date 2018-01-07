TARGET = create
CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags glfw3` 
INCLUDES = -I/home/jack/Dev/Projects/create/include/ 
LIBS = -lGL -lGLU -lglut -lGLEW `pkg-config --static --libs glfw3`
SRC = $(wildcard source/*.c)

default: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) $(wildcard lib/*.a) $(INCLUDES) $(LIBS) -o $(TARGET)

clean:
	rm $(TARGET)

