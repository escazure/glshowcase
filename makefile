CXX = g++
CC  = gcc

TARGET = museum 

CXXFLAGS = -Iinclude -Iinclude/imgui -Iinclude/imgui/backends
CFLAGS   = -Iinclude

CPP_SRCS = \
	$(wildcard src/*.cpp) \
	include/imgui/imgui.cpp \
	include/imgui/imgui_draw.cpp \
	include/imgui/imgui_tables.cpp \
	include/imgui/imgui_widgets.cpp \
    include/imgui/backends/imgui_impl_glfw.cpp \
    include/imgui/backends/imgui_impl_opengl3.cpp

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
