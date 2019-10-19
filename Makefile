# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 17:48:56 by gwyman-m          #+#    #+#              #
#    Updated: 2019/10/19 23:57:11 by sts              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls

SRC_DIR = src/

FLAGS = -g -Wall -Wextra -Werror -I. -I libft/

LIB = -L libft/ -lft

HEADER = ft_ls.h

CFILES= main.c get_flags.c create_name.c queue.c init_flags.c

SRC = $(addprefix $(SRC_DIR),$(CFILES))

OBJ = $(SRC:%.c=%.o)

VPATH := src

.PHONY=all clean fclean re

RULE=$(firstword $(MAKECMDGOALS))

all: subm $(NAME)

subm:
ifneq (`ls libft`, "")
	git submodule init
	git submodule update
endif

$(NAME): $(OBJ)
	@make -C libft/
	gcc $(FLAGS) $(OBJ) -o $(NAME) $(LIB)
	@printf "\e[?25h\033[0;32mft_ls is ready\033[0m\n"

%.o: %.c $(HEADER)
	gcc -c $(FLAGS) $< -o $@
	@printf "\e[?25l\033[0;34mcompiling $<\033[0m\033\r"
	@printf "                                 \r"

clean:
	@rm -f $(OBJ)
ifneq ($(RULE), $(filter $(RULE), fclean re))
	@make clean -C libft/
endif
	@echo "\033[0;33mthe src directory is cleaned\033[0m"

fclean: clean
	@make fclean -C libft/
	@rm -f $(NAME)
	@echo "\033[0;33mdeleted ft_ls\033[0m"

re: fclean all
