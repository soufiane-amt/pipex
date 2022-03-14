# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samajat <samajat@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/26 16:18:36 by samajat           #+#    #+#              #
#    Updated: 2022/03/14 15:11:00 by samajat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = pipex
NAME_BONUS = pipex_b
RM = rm -rf

GET_SRC = ${addprefix get_next_line/,get_next_line get_next_line_utils}

U_SRC = ${addprefix utils/,ft_putnbr_fd ft_putstr_fd ft_split ft_memcmp}

FILES = ${addprefix srcs/, $(GET_SRC) $(U_SRC)}

SRC = ${addsuffix .c, $(FILES) srcs/pipex}

SRC_OBJ = ${addsuffix .c, $(FILES) pipex_bonus/pipex_bonus}

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_OBJ:.c=.o)

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


bonus : $(OBJ_BONUS) $(HEADER)
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
