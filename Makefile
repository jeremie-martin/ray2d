TARGET_FILE		:= ray2d
ARGS			:= 
DEFINES			:=
SRC_FILES		:= main.cpp PointLight.cpp Color.cpp Obstacle/Obstacle.cpp Obstacle/Segment.cpp Ray.cpp Raytracer.cpp WindowWrapper.cpp Renderer.cpp
SRC_PREFIX		:= src/
INCLUDE_DIRS	:= include/
LIBRARY_DIRS	:= lib/
LIBRARY_FILES	:= -lpthread -lm -lglfw3 -lglfw3dll -lglew32 -lopengl32 -lgdi32 -lassimp -limgui -lgl3w -lbenchmark -lshlwapi
FLAGS			:= -O3 # -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
C_FLAGS			:= $(FLAGS) -std="c11"
CPP_FLAGS		:= $(FLAGS) -std="c++17"
LD_FLAGS		:= 
SRC_FILE_TYPES	:= .c .cpp
ALL_SRC_FILES	:= $(wildcard $(addprefix $(SRC_PREFIX),$(addsuffix /*,$(SRC_FOLDERS))))
SRC_FILES		:= $(addprefix $(SRC_PREFIX),$(SRC_FILES)) \
					$(filter $(addprefix %,$(SRC_FILE_TYPES)),$(ALL_SRC_FILES))
DEFINES			:= $(addprefix -D,$(DEFINES))
INCLUDE_DIRS	:= -I$(INCLUDE_DIRS)
LIBRARY_DIRS	:= $(addprefix -L,$(LIBRARY_DIRS))
OUTPUT_DIR		:= bin/
OBJ_DIR			:= obj/
O_FILES			:= $(addprefix $(OBJ_DIR),$(addsuffix .o,$(SRC_FILES)))
TARGET			:= $(OUTPUT_DIR)$(TARGET_FILE)
O_DIRS			:= $(sort $(dir $(O_FILES)))
CC				:= gcc
CXX				:= g++
LD				:= $(CXX)
RUN				:= ./$(TARGET) $(ARGS)

$(TARGET): _makedirs $(O_FILES)
	$(LD) $(LD_FLAGS) $(LIBRARY_DIRS) $(O_FILES) $(LIBRARY_FILES) -o $@

$(OBJ_DIR)%.c.o: %.c
	$(CC) -c $(DEFINES) $(INCLUDE_DIRS) $(C_FLAGS) $< -o $@

$(OBJ_DIR)%.cpp.o: %.cpp
	$(CXX) -c $(DEFINES) $(INCLUDE_DIRS) $(CPP_FLAGS) $< -o $@

_makedirs:
	mkdir -p $(O_DIRS) $(OUTPUT_DIR)

clean:
	rm -fr $(OBJ_DIR) $(OUTPUT_DIR)

run:
	$(RUN)

.PHONY: _makedirs clean run info
