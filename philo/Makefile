# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/10 13:10:37 by dpalmer           #+#    #+#              #
#    Updated: 2023/03/30 10:14:47 by dpalmer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=	philo

SRC_DIR		=	src/
OBJ_DIR		=	obj/
INCLUDE	 	=	-I include

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -O2 #-fsanitize=thread
ADDON		=	-pthread

# Colors

C_RESET = \033[0;39m
GREEN = \033[0;92m
YELLOW = \033[0;93mmkd
BLUE = \033[0;94m
B_MAGENTA = \033[1;35m
CYAN = \033[0;96m

#Sources

SRC_FILES	=	main				\
				parse_args			\
				init				\
				utils				\
				action				\
				check_death


SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

###

all:		$(NAME)

$(NAME):	$(OBJ)
			@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(ADDON)
			@echo "$(B_MAGENTA)$(NAME) compiled successfully$(C_RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			@mkdir -p $(OBJ_DIR)
			@echo "$(GREEN)Compiling: $(BLUE)$<$(C_RESET)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			@rm -rf $(OBJ_DIR)
			@echo "$(BLUE)$(NAME) objects deleted.$(C_RESET)"


fclean:		clean
			@rm -f $(NAME)
			@echo "$(CYAN)$(NAME) executable deleted.$(C_RESET)"

re:			fclean all

.PHONY:		all clean fclean re
