# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/02 13:10:10 by dverbyts          #+#    #+#              #
#    Updated: 2017/11/29 17:19:58 by dverbyts         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

CFLAGS = -Wall -Wextra -Werror

SRC = vm.c vm_init_memory.c vm_read.c vm_helps.c ncurses.c vm_commands1.c \
vm_commands2.c vm_commands3.c vm_commands4.c vm_commands_help.c \
vm_commands_help2.c vm_game1.c vm_game2.c vm_read2.c ncurses_norm.c \
ncurses_norma.c norm.c vm_read3.c

OBJ = $(SRC:.c=.o)

LIB = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@echo "\033[32;1m<corewar libft>		| done\033[0m"
	@gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIB) -lncurses
	@echo "\033[32;1m<corewar>		| done\033[0m"

%.o: %.c
	@gcc $(CFLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJ)
	@make clean -C libft
	@echo "\033[1;33m<corewar libft *.o>	| removed\033[0m"
	@echo "\033[1;33m<corewar *.o>		| removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft
	@echo "\033[1;33m<corewar>		| removed\033[0m"

re: fclean all
