############
# mmr-sfml #
############

FILES = src/*.cxx ext/CGF/source/*.cpp
CC_FLAGS = -w
LK_FLAGS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
INC = -Iinclude -Iext/CGF/include
OUT = -o bin/mmr

CC = g++
STD = -std=c++11

all: mmr

mmr: $(FILES)
	$(CC) $(STD) $(FILES) $(INC) $(CC_FLAGS) $(LK_FLAGS) $(OUT)
