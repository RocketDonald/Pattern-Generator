CXX = g++
CFLAGS = -g -Wall
SRCS = Main.cpp Canvas.cpp Pixel.cpp

all: main

main: Main.o Canvas.o Pixel.o
	$(CXX) $(CFLAGS) -o main Main.o Canvas.o Pixel.o

Main.o: Canvas.h Canvas.cpp Main.cpp
	$(CXX) $(CFLAGS) -c Main.cpp

Canvas.o: Canvas.h Canvas.cpp Pixel.h  Pixel.h Pixel.cpp stb_image.h stb_image_write.h
	$(CXX) $(CFLAGS) -c Canvas.cpp

Pixel.o: Pixel.h Pixel.cpp
	$(CXX) $(CFLAGS) -c Pixel.cpp

clean:
	rm -f main Main.o Canvas.o 
