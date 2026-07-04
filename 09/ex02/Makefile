# -->┊( NAMES )┊.´-★☆★
NAME	=	PmergeMe

# -->┊( COMMANDS AND FLAGS )┊.´-★☆★
CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -g -std=c++98 -D DEBUG=$(DEBUG)
VAL			=	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s
DEBUG		=	0

# -->┊( DIRECTORIES )┊.´-★☆★
SRC_DIR	=	src
OBJ_DIR	=	obj

# -->┊( SOURCE AND OBJS )┊.´-★☆★
SOURCE	=	main.cpp PmergeMe.cpp

SRC		=	$(addprefix $(SRC_DIR)/, $(SOURCE))
OBJS	=	$(addprefix $(OBJ_DIR)/, $(SOURCE:.cpp=.o))


# -->┊( COMPILATION RULES )┊.´-★☆★
all: $(NAME)

$(NAME): $(OBJS)
	$(M_COMOBJS)
	$(M_COM)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)


# -->┊( STANDARD RULES )┊.´-★☆★
clean:
	$(M_REMOBJS)
	@rm -rf $(OBJ_DIR)

fclean: clean
	$(M_REM)
	@rm -rf $(NAME)

re:	fclean all
	$(M_RE)


# -->┊( EXECUTION RULES )┊.´-★☆★
exe: all
	./$(NAME) 6 14 5 12 1 3 7 13 8 2 11 15 4 10 9 16

rexe: re
	@echo "\n"
	./$(NAME) 11 2 17 0 16 8 6 15 10 3 21 1 18 9 14 19 12 5 4 20 13 7

val: all
	$(VAL) ./$(NAME)  28 12 6 22 25 30 7 13 18 11 3 4 17 23 15 1 20 21 10 16 19 26 2 8 29 27 5 14 24 9

debug:
	make all DEBUG=1
	./$(NAME) `shuf -i 1-30 -n 30 | tr "\n" " "`

.PHONY: all clean fclean re exe rexe val debug


# -->┊( COSMETICS )┊.´-★☆★

#-‵,┊ normal colors
DEF	=	\e[0;39m
BLK	=	\e[0;30m
BLU	=	\e[0;34m
MAG =	\e[0;35m
GRN	=	\e[0;32m

#-‵,┊ bold colors
BCYN	=	\e[1;36m
BBLU	=	\e[1;34m

#-‵,┊ background colors
CYNB	=	\e[46m
YELB	=	\e[43m
BLUB	=	\e[44m

#-‵,┊ messages
M_COMOBJS	= @echo "$(BLK)-->┊$(GRN)  Compiling: $(BBLU)$(NAME)/objs $(BLK)$(DEF)"
M_COM		= @echo "$(BLK)-->┊$(GRN)  Compiling: $(DEF)$(BLUB) $(NAME) $(BLK)$(DEF)\n"
M_REMOBJS	= @echo "$(BLK)-->┊$(BLU)  Removing: $(BBLU) $(NAME)/objs $(BLK)$(DEF)"
M_REM		= @echo "$(BLK)-->┊$(BLU)  Removing:  $(DEF)$(BLUB) $(NAME) $(BLK)$(DEF)\n"
M_RE		= @echo "$(BLK)... $(BLU)  Re Done   $(DEF)$(BCYN) ($(NAME) is ready !!)$(DEF)"
