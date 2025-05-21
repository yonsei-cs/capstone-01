# 컴파일러 및 플래그
CXX := g++
CXXFLAGS := -std=c++17 -Wall -O2

# 소스 및 타겟
SRC := main.cpp columns.cpp utils.cpp
OBJ := $(SRC:.cpp=.o)
TARGET := main

# 라이브러리
LIBS := -lsqlite3
INCLUDES :=

# 기본 빌드 타겟
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# 정리
clean:
	rm -f $(OBJ) $(TARGET)
