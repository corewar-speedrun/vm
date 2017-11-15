# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/02 13:10:10 by dverbyts          #+#    #+#              #
#    Updated: 2017/11/02 13:10:11 by dverbyts         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

CFLAGS = -Wall -Wextra -Werror -g 

SRC = vm.c vm_init_memory.c vm_read.c vm_helps.c ncurses.c vm_commands1.c \
vm_commands2.c vm_commands3.c vm_commands4.c vm_commands_help.c \
vm_commands_help2.c vm_game1.c vm_game2.c

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
