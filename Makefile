# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samajat <samajat@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/26 16:18:36 by samajat           #+#    #+#              #
#    Updated: 2022/03/25 14:22:44 by samajat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = pipex
NAME_BONUS = pipex
RM = rm -rf

GET_SRC = ${addprefix get_next_line/,get_next_line get_next_line_utils}

U_SRC = ${addprefix utils/,ft_putnbr_fd ft_putstr_fd ft_split ft_memcmp t_free ft_allocate_arr}

FILES = ${addprefix srcs/, $(GET_SRC) $(U_SRC) exec_cmd check_syntax free_file data_collect}

SRC = ${addsuffix .c, $(FILES) srcs/pipex pipex_bonus/here_doc}

SRC_BON = ${addsuffix .c, $(FILES) pipex_bonus/pipex_bonus pipex_bonus/generate_pipes pipex_bonus/here_doc}

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BON:.c=.o)

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


bonus :LOGO_B $(OBJ_BONUS) $(HEADER)
	@printf "$(CURVE) $(MAGENTA)-Compiling files ...$(RESET)\n"
	@$(CC) $(FLAGS) -o $(NAME_BONUS) $(OBJ_BONUS)
	@printf "$(YELLOW) -Executable file $(NAME_BONUS) has been created.$(RESET)\n"

%.o	: %.c $(HEADER)
	@$(CC) -c $< -o $@
	@printf "$(CURVE)$(GRAY) -Generating object file $(notdir $@) from $(notdir $<)$(RESET)\n"

clean :
		@$(RM) $(OBJ) $(OBJ_BONUS)
		@printf "$(RED)Deleting object files ...$(RESET)\n"

fclean	: clean
		@printf "$(RED)Deleting executables ... $(RESET)\n"
		@$(RM) $(NAME) $(NAME_BONUS)

re		: fclean all

LOGO	:	
	@echo "$(Blue)██████╗░██╗██████╗░███████╗██╗░░██╗"
	@echo " ██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝"
	@echo " ██████╔╝██║██████╔╝█████╗░░░╚███╔╝░"
	@echo " ██╔═══╝░██║██╔═══╝░██╔══╝░░░██╔██╗░"
	@echo " ██║░░░░░██║██║░░░░░███████╗██╔╝╚██╗"
	@echo " ╚═╝░░░░░╚═╝╚═╝░░░░░╚══════╝╚═╝░░╚═╝"

LOGO_B	:
	@echo "$(Blue)██████╗░██╗██████╗░███████╗██╗░░██╗  ██████╗░░█████╗░███╗░░██╗██╗░░░██╗░██████╗"
	@echo " ██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝  ██╔══██╗██╔══██╗████╗░██║██║░░░██║██╔════╝"
	@echo " ██████╔╝██║██████╔╝█████╗░░ ╚███╔╝░  ██████╦╝██║░░██║██╔██╗██║██║░░░██║╚█████╗░"
	@echo " ██╔═══╝░██║██╔═══╝░██╔══╝░░░██╔██╗░  ██╔══██╗██║░░██║██║╚████║██║░░░██║░╚═══██╗"
	@echo " ██║░░░░░██║██║░░░░░███████╗██╔╝╚██╗  ██████╦╝╚█████╔╝██║░╚███║╚██████╔╝██████╔╝"
	@echo " ╚═╝░░░░░╚═╝╚═╝░░░░░╚══════ ╚═╝░░╚═╝  ╚═════╝░░╚════╝░╚═╝░░╚══╝░╚═════╝░╚═════╝░"
	
