CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = flappy_bird

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(EXEC)