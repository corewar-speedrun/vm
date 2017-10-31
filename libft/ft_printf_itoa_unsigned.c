/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoa_unsigned.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 19:04:49 by dverbyts          #+#    #+#             */
/*   Updated: 2017/08/31 19:04:53 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_printf_itoa_hash(int base, t_arg *s)
{
	if (s->j5 % base == 10 || s->j6 % base == 10)
		return (s->data > 96 ? 'a' : 'A');
	else if (s->j5 % base == 11 || s->j6 % base == 11)
		return (s->data > 96 ? 'b' : 'B');
	else if (s->j5 % base == 12 || s->j6 % base == 12)
		return (s->data > 96 ? 'c' : 'C');
	else if (s->j5 % base == 13 || s->j6 % base == 13)
		return (s->data > 96 ? 'd' : 'D');
	else if (s->j5 % base == 14 || s->j6 % base == 14)
		return (s->data > 96 ? 'e' : 'E');
	else if (s->j5 % base == 15 || s->j6 % base == 15)
		return (s->data > 96 ? 'f' : 'F');
	return ('0');
}

t_arg	*ft_printf_flags_unsigned(t_arg *s)
{
	if (s->t == 1)
		s->j6 = (ptrdiff_t)s->buf;
	else if (s->z == 1)
		s->j6 = (size_t)s->buf;
	else if (s->j == 1)
		s->j6 = (uintmax_t)s->buf;
	else if (s->ll == 1)
		s->j6 = (unsigned long long)s->buf;
	else if (s->l == 1)
		s->j6 = (unsigned long)s->buf;
	else if (s->h == 1 || ((s->data == 'O' || s->data == 'U') && s->hh == 1))
		s->j6 = (unsigned short)s->buf;
	else if (s->hh == 1)
		s->j6 = (unsigned char)s->buf;
	else
		s->j6 = (unsigned int)s->buf;
	return (s);
}

int		ft_printf_itoa_unsignedlen(t_arg *s, int b)
{
	int						len;
	unsigned long long int	n;

	n = s->j6;
	len = 1;
	while (n != 0)
	{
		n = n / b;
		len++;
	}
	return (len);
}

char	*ft_printf_itoa_unsigmake(t_arg *s, char *r, int minf, int base)
{
	char					*buf;

	s->j3 = s->j2 - 1;
	if (!(buf = (char *)malloc(sizeof(char) * s->j2)))
		return (0);
	while ((ptrdiff_t)s->l4 < s->j3)
	{
		if (s->j6 % base < 10)
			buf[s->l4++] = s->j6 % base + '0';
		else
			buf[s->l4++] = ft_printf_itoa_hash(base, s);
		s->j6 = s->j6 / base;
	}
	buf[s->l4] = '\0';
	r = ft_printf_itoa_rev(buf, r, s, minf);
	if (buf)
		free(buf);
	return (r);
}

char	*ft_printf_itoa_unsigned(t_arg *s, int base, int minf)
{
	char					*re;

	s->l5 = 0;
	s = ft_printf_flags_unsigned(s);
	if (s->j6 == 0)
		return (ft_strdup("0\0"));
	s->j2 = ft_printf_itoa_unsignedlen(s, base);
	if (!(re = (char *)malloc(sizeof(char) * s->j2)))
		return (0);
	s->str = ft_printf_itoa_unsigmake(s, re, minf, base);
	return (re);
}
