EXEC = avm

SRC_FILES = main.cpp \
			Lexer.cpp \
			avmException.cpp

SRC = $(addprefix src/, $(SRC_FILES))

OBJ = $(SRC:.cpp=.o)

INC = -I./inc

CC = clang++

CCFLAGS = -Wall -Wextra -Werror -std=c++11

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CCFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(EXEC)

re: fclean all

r: all
	./$(EXEC)

rf: all
	./$(EXEC) test/test1


.phony: all clean fclean re
