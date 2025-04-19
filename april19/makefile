CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++11

SRCS = main.cpp Cpu.cpp Memory.cpp Opcodes.cpp OS.cpp MemoryPager.cpp PageTable.cpp globals.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = ncc

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
