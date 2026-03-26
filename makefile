CXX = g++
CC  = gcc

TARGET = museum 

CXXFLAGS = -Iinclude -Iassimp/include 
CFLAGS   = -Iinclude

CPP_SRCS = \
	$(wildcard src/*.cpp) \

C_SRCS = \
	$(wildcard src/*.c)

CPP_OBJS = $(CPP_SRCS:.cpp=.o)
C_OBJS   = $(C_SRCS:.c=.o)
OBJS     = $(CPP_OBJS) $(C_OBJS)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ -Llibs -lassimp -lglfw -ldl -lGL -Wl,-rpath=./libs

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
