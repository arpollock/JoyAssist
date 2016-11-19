CXX = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFLAGS += -I/usr/local/include/
LDFLAGS = -L/usr/local/lib/
LDFLAGS += -lserialport
LDFLAGS += -framework ApplicationServices
LDFLAGS += -lsfml-graphics -lsfml-window -lsfml-system

TARGET = thumby
SRCDIR = ./
SRCS = $(wildcard $(SRCDIR)*.cpp)
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean run

all: $(TARGET) run clean

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

-include $(DEPS)
