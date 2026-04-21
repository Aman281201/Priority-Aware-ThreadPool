CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread

TARGET = threadpool_test
SRCS = main.cpp
HEADERS = threadpool.h

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)
