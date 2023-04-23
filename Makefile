# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acouture <acouture@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 10:52:08 by acouture          #+#    #+#              #
#    Updated: 2023/03/06 11:27:21 by acouture         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		pipex

S = 		src/

SRC =		$(addprefix $(S), pipex.c pipex_utils.c errors.c)



OBJS = 		*.o

CC = 		gcc

FLAGS = 	-g -Wall -Werror -Wextra

NONE='\033[0m'
GREEN='\033[32m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(CURSIVE)$(GRAY) "     - Making libft..." $(NONE)
	@make -C $(LIBF_DIR)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@gcc  $(FLAGS) $(OBJS) $(LIBFT) $(LINKS) -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(OBJS): $(SRC)
	@echo $(CURSIVE)$(GRAY) "     - Making object files..." $(NONE)
	@gcc -c $(FLAGS) $(SRC)

exe: all
	@echo "     - Executing $(NAME)... \n"
	@./$(NAME)
	@echo "\n     - Done -"

clean:
	@echo $(CURSIVE)$(GRAY) "     - Removing object files..." $(NONE)
	@rm -rf $(OBJS) *.txt
	@make -C $(LIBF_DIR) clean

fclean: clean
	@echo $(CURSIVE)$(GRAY) "     - Removing $(NAME)..." $(NONE)
	@rm -rf $(NAME)
	@make -C $(LIBF_DIR) fclean

re: fclean all

.PHONY: all exe clean fclean re