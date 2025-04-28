CC = g++

CFLAGS = -Wall -g

LDFLAGS = -lSDL2 -lSDL2_ttf

TARGET = flappy

SOURCE = flappy.cpp

OBJECT = $(SOURCE:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECT)
	$(CC) $(OBJECT) -o $(TARGET) $(LDFLAGS)

$(OBJECT): $(SOURCE)
	$(CC) $(CFLAGS) -c $(SOURCE) -o $(OBJECT)

clean:
	rm -f $(OBJECT) $(TARGET)

.PHONY: all clean
