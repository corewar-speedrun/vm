# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/25 21:55:52 by dverbyts          #+#    #+#              #
#    Updated: 2016/11/25 21:55:56 by dverbyts         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror -I.

FT = ft_isalnum.c ft_isascii.c ft_isprint.c ft_putchar_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_putstr_fd.c ft_strclr.c ft_strequ.c ft_memnclr.c ft_strnequ.c \
ft_toupper.c ft_isalpha.c ft_isdigit.c ft_putchar.c ft_putendl.c ft_putnbr.c \
ft_putstr.c ft_strcat.c ft_strcpy.c ft_strlen.c ft_strncpy.c ft_tolower.c \
ft_strlenint.c ft_strncat.c ft_strcmp.c ft_strncmp.c ft_strlcat.c ft_strdup.c \
ft_bzero.c ft_memcpy.c ft_memmove.c ft_memccpy.c ft_memset.c ft_memchr.c \
ft_memcmp.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c ft_atoi.c \
ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strsplit.c ft_strtrim.c \
ft_strsub.c ft_strjoin.c ft_itoa.c ft_striter.c ft_striteri.c ft_strmap.c \
ft_strmapi.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
ft_lstmap.c ft_lstpush.c ft_lstlen.c ft_atoi_16.c get_next_line.c \
ft_printf.c ft_printf_data_c.c ft_printf_data_d.c \
ft_printf_data_p_u_x_o.c ft_printf_data_print.c ft_printf_data_s_wchar_t.c \
ft_printf_format_parsing.c ft_printf_help1.c ft_printf_itoa.c \
ft_printf_itoa_unsigned.c ft_printf_make_mem.c ft_printf_split_format.c \
ft_atoi_base.c ft_itoa_base.c

OBJ = $(FT:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c
	@gcc $(CFLAGS) -c -o $@ $<

clean:
	@rm -rf $(OBJ)
	
fclean: clean
	@rm -rf $(NAME)

re: fclean all
