CC = g++
CFLAGS = -g -Wall

TARGET = app_main
LINKS = game.cpp levelgen.cpp brick.cpp ball.cpp player.cpp

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	  $(CC) $(CFLAGS) -o $(TARGET) $(LINKS) $(TARGET).cpp $(LIBS)

clean:
	  $(RM) $(TARGET)