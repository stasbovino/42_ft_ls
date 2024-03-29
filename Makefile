# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 17:48:56 by gwyman-m          #+#    #+#              #
#    Updated: 2019/11/09 17:00:28 by gwyman-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls

SRC_DIR = src/

FLAGS = -g -Wall -Wextra -Werror -I. -I libft/

LIB = -L libft/ -lft

HEADER = ft_ls.h

CFILES= main.c get_flags.c init_flags.c error.c args.c obj.c sort.c print_dir.c \
		print.c format.c print_list.c get_link_info.c \

SRC = $(addprefix $(SRC_DIR),$(CFILES))

OBJ = $(SRC:%.c=%.o)

VPATH := src

submodule = `git submodule | grep "-"`

.PHONY = submodule all clean fclean re

.SILENT: subm

RULE=$(firstword $(MAKECMDGOALS))

all: subm $(NAME)

.PHONY: subm all clean fclean re

subm:
	if [[ -n $(submodule) ]]; then\
		git submodule init;\
		git submodule update;\
	fi

$(NAME): $(OBJ)
	@make -C libft/
	@gcc $(FLAGS) $(OBJ) -o $(NAME) $(LIB)
	@printf "\e[?25h\033[0;32mft_ls is ready\033[0m\n"

%.o: %.c $(HEADER)
	@gcc -c $(FLAGS) $< -o $@
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
