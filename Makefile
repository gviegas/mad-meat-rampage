############
# mmr-sfml #
############

#release
FILES = src/*.cxx ext/CGF/source/*.cpp
CC_FLAGS = -w
LK_FLAGS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network
#INC = -Lext/SFML-2.3.2/lib -Lext/CGF/lib -Iinclude -Iext/SFML-2.3.2/include -Iext/CGF/include
INC = -Iinclude -Iext/CGF/include
OUT = -o bin/mmr

#test
FILES_T = test/*.cxx
CC_FLAGS_T = -Wall -Wextra
#LK_FLAGS_T = $(LK_FLAGS)
LK_FLAGS_T = -lsfml-system -lsfml-window -lsfml-graphics
#INC_T = $(INC)
INC_T = -Iinclude -Lext/SFML-2.3.2/lib
OUT_T = -o bin/test_mmr

#general
CC = g++
STD = -std=c++11

all: $(FILES)
	$(CC) $(STD) $(FILES) $(INC) $(CC_FLAGS) $(LK_FLAGS) $(OUT)

test: $(FILES_T)
	$(CC) $(STD) $(FILES_T) $(INC_T) $(CC_FLAGS_T) $(LK_FLAGS_T) $(OUT_T)