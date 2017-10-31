/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_data_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 17:13:38 by dverbyts          #+#    #+#             */
/*   Updated: 2017/08/05 17:13:39 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_data_print(t_arg *s)
{
	s->l5 = 0;
	if ((s->data == 'c' || s->data == 'C') && s->buf == NULL)
	{
		while (s->str)
		{
			write(1, &s->str[s->l5], 1);
			s->re++;
			if (s->str[s->l5] == '\0')
				return ;
			else
				s->l5++;
		}
	}
	while (s->str[s->l5] != '\0')
	{
		write(1, &s->str[s->l5++], 1);
		s->re++;
	}
	return ;
}

char	*ft_printf_prs(char *f, t_arg *s)
{
	char *r;

	r = ft_strnew(1);
	r[0] = f[s->l2++];
	if (s->buf == NULL)
	{
		if (s->minus == 1 && s->zero == 1)
			s->zero = 0;
		s->accuracy = -1;
		s->plus = 0;
		s->spase = 0;
		s->data = 's';
		s->buf = r;
		if (f[s->l2] != '\0')
			return (ft_printf_prs2(f, s));
	}
	else
	{
		s->buf = ft_strjoin((char *)s->buf, r);
		if (s->accuracy == 0)
			s->accuracy = -1;
		s->prs = 0;
	}
	return (f);
}

char	*ft_printf_prs2(char *f, t_arg *s)
{
	char *r;

	s->l1 = 0;
	r = ft_strnew(ft_strlen(f) - (s->l2 - 1));
	while (f[s->l2])
		r[s->l1++] = f[s->l2++];
	r[s->l1] = '\0';
	ft_printf_write_data(f, s);
	ft_printf_clear_t_arg(s);
	f = r;
	return (f);
}

void	ft_printf_nonf(char *f, t_arg *s)
{
	s->prs = 0;
	s->tmp1 = ft_strnew(1);
	s->tmp1[0] = f[s->l2++];
	if (s->buf == NULL)
		s->buf = ft_strdup(s->tmp1);
	else
		s->buf = ft_strjoin((char *)s->buf, s->tmp1);
	if (s->width > 0 && s->width > (int)ft_strlen((char *)s->buf))
		s->zero == 1 ? ft_printf_nonf2(s, '0') : ft_printf_nonf2(s, ' ');
	if (s->accuracy == 0)
		s->accuracy = -1;
	while (f[s->l2] != '\0' && f[s->l2] != '%')
	{
		s->tmp1[0] = f[s->l2++];
		s->buf = ft_strjoin((char *)s->buf, s->tmp1);
	}
	if ((f[s->l2] == '\0' || f[s->l2] == '%') && s->spase == 1)
		s->spase = 0;
	if (s->buf != NULL)
	{
		ft_printf_data_ss(0, (char *)s->buf, s);
		ft_printf_clear_t_arg2(s);
	}
}

void	ft_printf_nonf2(t_arg *s, char t)
{
	s->tmp1 = ft_strdup((char *)s->buf);
	s->l1 = 0;
	s->l3 = (int)ft_strlen(s->tmp1);
	s->l4 = s->width - s->l3;
	s->tmp2 = ft_strnew(s->l3 + s->l4);
	if (s->minus == 1)
	{
		while (s->l5 < s->l3 && s->tmp1[s->l1] != '\0')
			s->tmp2[s->l5++] = s->tmp1[s->l1++];
		while (s->l5 < (s->l3 + s->l4))
			s->tmp2[s->l5++] = t;
	}
	else
	{
		while (s->l5 < s->l4)
			s->tmp2[s->l5++] = t;
		while (s->l5 < (s->l3 + s->l4) && s->tmp1[s->l1] != '\0')
			s->tmp2[s->l5++] = s->tmp1[s->l1++];
	}
	s->tmp2[s->l5] = '\0';
	free(s->buf);
	s->buf = ft_strdup(s->tmp2);
	return ;
}
