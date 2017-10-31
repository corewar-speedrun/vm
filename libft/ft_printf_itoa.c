/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:27:38 by dverbyts          #+#    #+#             */
/*   Updated: 2017/08/20 17:27:40 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_printf_itoa_rev(char *src, char *dst, t_arg *s, int min)
{
	int		count;

	--s->j2;
	count = ft_strlen(src) - 1;
	s->j1 = 0;
	if (min == 1)
	{
		dst[s->j1] = '-';
		s->j1++;
		s->j2--;
	}
	while (s->j2)
	{
		dst[s->j1++] = src[count--];
		s->j2--;
	}
	if (src[0] == 0)
		dst[0] = '0';
	dst[s->j1] = '\0';
	return (dst);
}

t_arg	*ft_printf_flags_signed(t_arg *s)
{
	if (s->t == 1)
		s->j5 = (ptrdiff_t)s->buf;
	else if (s->z == 1)
		s->j5 = (size_t)s->buf;
	else if (s->j == 1)
		s->j5 = (intmax_t)s->buf;
	else if (s->ll == 1 || (s->data == 'D' && s->hh == 1))
		s->j5 = (long long)s->buf;
	else if (s->l == 1)
		s->j5 = (long)s->buf;
	else if (s->h == 1)
		s->j5 = (short int)s->buf;
	else if (s->hh == 1)
		s->j5 = (signed char)s->buf;
	else
		s->j5 = (int)s->buf;
	return (s);
}

int		ft_printf_itoa_len(t_arg *s, int b)
{
	int			len;
	ptrdiff_t	n;

	n = s->j5;
	len = 1;
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n != 0)
	{
		n = n / b;
		len++;
	}
	return (len);
}

char	*ft_printf_itoa_make(t_arg *s, char *r, int minf, int base)
{
	char		*buf;

	s->j3 = s->j2 - 1;
	if (!(buf = (char *)malloc(sizeof(char) * s->j2)))
		return (0);
	if (minf == 1)
	{
		s->j4 = s->j5 * -1;
		s->j3--;
	}
	else
		s->j4 = s->j5;
	while ((ptrdiff_t)s->l4 < s->j3)
	{
		if (s->j4 % base < 10)
			buf[s->l4++] = s->j4 % base + '0';
		else
			buf[s->l4++] = ft_printf_itoa_hash(base, s);
		s->j4 = s->j4 / base;
	}
	buf[s->l4] = '\0';
	r = ft_printf_itoa_rev(buf, r, s, minf);
	if (buf)
		free(buf);
	return (r);
}

char	*ft_printf_itoa(t_arg *s, int b, int minf)
{
	char		*re;

	if (s->t == 1 || s->z == 1 || s->j == 1 || s->ll == 1 || s->h == 1 ||
		s->hh == 1 || s->l == 1 || s->data == 'D')
	{
		s->l5 = 0;
		s = ft_printf_flags_signed(s);
		if (s->j5 == 0)
			return (ft_strdup("0\0"));
		if (s->j5 < 0)
			minf = 1;
		s->j2 = ft_printf_itoa_len(s, b);
		if (!(re = (char *)malloc(sizeof(char) * s->j2)))
			return (0);
		s->str = ft_printf_itoa_make(s, re, minf, b);
	}
	else
		re = ft_itoa((int)s->buf);
	return (re);
}
