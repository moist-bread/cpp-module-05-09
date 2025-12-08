# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rduro-pe <rduro-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 12:30:07 by rduro-pe          #+#    #+#              #
#    Updated: 2025/12/08 12:51:47 by rduro-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -->┊( NAMES )┊.´-★☆★
NAME	=	mommy

# -->┊( COMMANDS AND FLAGS )┊.´-★☆★
CXX	=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -g -std=c++98
VAL		=	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s

# -->┊( DIRECTORIES )┊.´-★☆★
SRC_DIR	=	src
OBJ_DIR	=	obj

# -->┊( SOURCE AND OBJS )┊.´-★☆★
SOURCE	=	main.cpp Bureaucrat.cpp

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


# -->┊( EXECUTION RULES )┊.´-★☆★
exe: all
	./$(NAME) 4

rexe: re
	@echo "\n"
	./$(NAME) 148

val: all
	$(VAL) ./$(NAME) 151

# -->┊( STANDARD RULES )┊.´-★☆★
clean:
	$(M_REMOBJS)
	@rm -rf $(OBJ_DIR)

fclean: clean
	$(M_REM)
	@rm -rf $(NAME)

re:	fclean all
	$(M_RE)

.PHONY: all clean fclean re rexe


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