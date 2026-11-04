CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = Lab10

all: $(TARGET)

$(TARGET): Lab10.cpp
  $(CXX) $(CXXFLAGS) -o $(TARGET) Lab10.cpp

clean:
  rm -f $(TARGET)
