# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/02 13:10:10 by dverbyts          #+#    #+#              #
#    Updated: 2017/11/20 09:59:40 by dmaznyts         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

CFLAGS = -Wall -Wextra -Werror -g -O3

SRC = vm.c vm_init_memory.c vm_read.c vm_helps.c ncurses.c vm_commands1.c \
vm_commands2.c vm_commands3.c vm_commands4.c vm_commands_help.c \
<<<<<<< HEAD
vm_commands_help2.c vm_game1.c vm_game2.c vm_read2.c ncurses_norm.c \
ncurses_norma.c norm.c
=======
vm_commands_help2.c vm_game1.c vm_game2.c vm_read2.c vm_read3.c
>>>>>>> 8b90da6567beeb066a11ebc75c7b83c7138aadc9

OBJ = $(SRC:.c=.o)

LIB = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIB) -lncurses

%.o: %.c
	@gcc $(CFLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJ)
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all
