/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 20:49:09 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/21 22:22:05 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdarg.h>
# include <inttypes.h>
# include <stddef.h>

# define BUFF_SIZE 1

typedef struct			s_line
{
	char				*l;
	int					n_fd;
	struct s_line		*next;
}						t_line;

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

typedef	struct			s_arg
{
	int					hh;
	int					h;
	int					l;
	int					ll;
	int					j;
	int					z;
	int					t;
	int					lll;
	int					re;
	int					prs;
	int					accuracy;
	int					width;
	int					minus;
	int					plus;
	int					spase;
	int					hash;
	int					zero;
	char				**arg;
	char				*str;
	void				*buf;
	int					l1;
	int					l2;
	int					l3;
	int					l4;
	int					l5;
	ptrdiff_t			j1;
	ptrdiff_t			j2;
	ptrdiff_t			j3;
	unsigned long long	j4;
	ptrdiff_t			j5;
	unsigned long long	j6;
	int					data;
	wchar_t				*wchar;
	char				*tmp1;
	char				*tmp2;
}						t_arg;

/*
**	int			hh;  флаг размера
**	int			h; флаг размера
**	int			l; флаг размера
**	int			ll; флаг размера
**	int			j; флаг размера
**	int			z; флаг размера
**	int			t; флаг размера
**	int			L; флаг размера
**	int			re; сколько символов напечатано
**	int			accuracy; точность
**	int			width; ширина
**	int			minus; флаг
**	int			plus; флаг
**	int			spase; флаг
**	int			hash; флаг
**	int			zero; флаг
**	char		**arg; условия, которые зашли, const char *format,
**	char		*str; буфер для записи вывода на экран
**	void		*buf; буфер для получения данных из va_list args
**	int			l1; счетчик 1
**	int			l2; счетчик 2
**	int			l3; счетчик 3
**	int			l4; счетчик 4
**	int			data; тип данных.
*/

int						ft_toupper(int buf);
int						ft_tolower(int buf);
char					*ft_strncpy(char *dest, const char *sors, size_t n);
char					*ft_strcpy(char *dest, const char *sors);
void					ft_strclr(char *s);
size_t					ft_strlen(const char *string);
int						ft_strlenint(const char *string);
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
int						ft_strcmp(char const *s1, char const *s2);
int						ft_strncmp(char const *s1, char const *s2, size_t n);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
char					*ft_strstr(const char *big, const char *ltl);
char					*ft_strnstr(const char *big, const char *ltl,
						size_t len);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strncat(char *s1, const char *s2, size_t num);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putstr(char const *s);
void					ft_putnbr_fd(int n, int fd);
void					ft_putnbr(int n);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putendl(char const *s);
void					ft_putchar_fd(char c, int fd);
void					ft_putchar(char c);
int						ft_isprint(int test);
int						ft_isdigit(int test);
int						ft_isascii(int test);
int						ft_isalpha(int test);
int						ft_isalnum(int test);
char					*ft_strdup(const char *s1);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memccpy(void *dst, const void *src, int c,
						size_t n);
void					*ft_memset(void *b, int c, size_t len);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memnclr(void *s, size_t x);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_atoi(char *str);
void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);
char					*ft_strnew(size_t size);
void					ft_strdel(char **ap);
char					**ft_strsplit(char const *s, char c);
char					*ft_strtrim(char *s);
char					*ft_strsub(char const *s, unsigned int start,
						size_t len);
char					*ft_strjoin(char *t, char *y);
char					*ft_itoa(int n);
void					ft_striter(char *s, void (*f) (char *));
void					ft_striteri(char *s, void (*f) (unsigned int, char *));
char					*ft_strmap(char const *s, char (*f) (char));
char					*ft_strmapi(char const *s,
						char (*f) (unsigned int, char));
t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstdelone(t_list **alst,
						void (*del) (void *, size_t));
void					ft_lstdel(t_list **alst, void (*del) (void *, size_t));
void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstiter(t_list *lst, void (*f) (t_list *elem));
t_list					*ft_lstmap(t_list *lst, t_list *(*f) (t_list *elem));
void					ft_lstpush(t_list *cur,
						void *cont, size_t content_size);
int						ft_lstlen(t_list *lst);
int						ft_atoi_16(char *str);
int						get_next_line(const int fd, char **line);
char					*string(t_line **l);
t_line					*make_list(int fd);
int						read_file(t_line **lst, int fd);
int						ft_printf(const char *format, ...);
void					ft_printf_take_args(const char *format, va_list args,
						t_arg *s);
void					ft_printf_read_format(char *f, va_list args,
						t_arg *s);
void					ft_printf_write_data(char *f, t_arg *s);
int						ft_printf_flags(char f, t_arg *s);
void					ft_printf_accuracy(char *f, t_arg *s,
						va_list args);
void					ft_printf_width(char *f, t_arg *s, va_list args);
int						ft_printf_mods(char *f, t_arg *s);
int						ft_printf_data_type(char f, va_list args, t_arg *s);
int						ft_printf_data_type2(char f);
t_arg					*ft_printf_make_mem(void);
void					ft_printf_clear_t_arg(t_arg *s);
void					ft_printf_clear_t_arg2(t_arg *s);
void					ft_printf_del_arg(t_arg *del);
int						how_m_words(char const *str);
int						how_b(char const *str, int i);
char					**ft_printf_split_format(char const *f, int i, int args,
						int a);
char					*ft_printf_prs(char *f, t_arg *s);
char					*ft_printf_prs2(char *f, t_arg *s);
void					ft_printf_nonf(char *f, t_arg *s);
void					ft_printf_nonf2(t_arg *s, char t);
void					ft_printf_data_s(t_arg *s);
void					ft_printf_data_ss(char p, char *y, t_arg *s);
void					ft_printf_data_width(t_arg *s, char t);
void					ft_printf_data_width_c(t_arg *s, char t);
void					ft_printf_data_print(t_arg *s);
void					ft_printf_data_s_wchar_t(t_arg *s);
void					ft_printf_data_wchar_read(t_arg *s);
void					ft_printf_data_wchar_read2(t_arg *s);
void					ft_printf_data_wchar_width(t_arg *s, char t);
char					*ft_printf_wchar_decode(int t, t_arg *s, int z);
void					ft_printf_data_c(t_arg *s);
void					ft_printf_data_c2(t_arg *s);
void					ft_printf_data_c_wchar_t(t_arg *s);
void					ft_printf_data_d(t_arg *s);
void					ft_printf_data_d2(t_arg *s);
void					ft_printf_data_d3(t_arg *s);
void					ft_printf_data_ps(t_arg *s);
void					ft_printf_data_u(t_arg *s);
void					ft_printf_data_o(t_arg *s);
void					ft_printf_data_o2(t_arg *s);
void					ft_printf_data_x(t_arg *s);
char					*ft_printf_itoa(t_arg *s, int base, int minf);
char					*ft_printf_itoa_unsigned(t_arg *s, int base, int minf);
t_arg					*ft_printf_flags_unsigned(t_arg *s);
int						ft_printf_itoa_unsignedlen(t_arg *s, int b);
char					*ft_printf_itoa_unsigmake(t_arg *s, char *r, int minf,
						int base);
void					ft_printf_data_0x(t_arg *s);
t_arg					*ft_printf_flags_signed(t_arg *s);
char					*ft_printf_itoa_make(t_arg *s, char *r, int minf,
						int base);
char					*ft_printf_itoa_rev(char *src, char *dst, t_arg *s,
						int min);
int						ft_printf_itoa_len(t_arg *s, int b);
char					ft_printf_itoa_hash(int base, t_arg *s);
void					ft_printf_data_p(t_arg *s);
int						ft_printf_chek_data(char f);
int						ft_atoi_base(unsigned char *str, int str_base);
char					*ft_itoa_base(int value, int base);

#endif
