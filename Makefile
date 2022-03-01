# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samajat <samajat@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/26 16:18:36 by samajat           #+#    #+#              #
#    Updated: 2022/03/01 17:09:50 by samajat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = pipex
RM = rm -rf

GET_SRC = ${addprefix get_next_line/,get_next_line get_next_line_utils}

U_SRC = ${addprefix utils/,ft_putnbr_fd ft_putstr_fd ft_split ft_memcmp}

FILES = ${addprefix srcs/, pipex $(GET_SRC) $(U_SRC)}

SRC = $(FILES:=.c)

OBJ = $(SRC:.c=.o)

HEADER = includes/pipex.h

MAGENTA = \033[35m
RED = \e[1;31m
YELLOW = \e[93;5;226m
CURVE = \e[33;3m
RESET =  \e[0m
GRAY	=	\e[33;2;37m
Blue=	\033[0;94m\


all	: $(NAME)

$(NAME) :LOGO $(OBJ) $(HEADER)
	@printf "$(CURVE) $(MAGENTA)-Compiling files ...$(RESET)\n"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ)
	@printf "$(YELLOW) -Executable file $(NAME) has been created.$(RESET)\n"

%.o	: %.c $(HEADER)
	@$(CC) -c $< -o $@
	@printf "$(CURVE)$(GRAY) -Generating object file $(notdir $@) from $(notdir $<)$(RESET)\n"

clean :
		@$(RM) $(OBJ)
		@printf "$(RED)-Deleting $(notdir $(OBJ))$(RESET)\n"

fclean	: clean
		@printf "$(RED)-Deleting $(NAME)$(RESET)\n"
		@$(RM) $(NAME)

re		: fclean all

LOGO 	:
	@echo "$(Blue)██████╗░██╗██████╗░███████╗██╗░░██╗"
	@echo " ██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝"
	@echo " ██████╔╝██║██████╔╝█████╗░░░╚███╔╝░"
	@echo " ██╔═══╝░██║██╔═══╝░██╔══╝░░░██╔██╗░"
	@echo " ██║░░░░░██║██║░░░░░███████╗██╔╝╚██╗"
	@echo " ╚═╝░░░░░╚═╝╚═╝░░░░░╚══════╝╚═╝░░╚═╝"
