/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_data_d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 15:24:53 by dverbyts          #+#    #+#             */
/*   Updated: 2017/09/05 15:24:57 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_data_d(t_arg *s)
{
	if (s->data == 'D')
		s->l = 1;
	s->str = ft_printf_itoa(s, 10, 0);
	if ((ptrdiff_t)s->buf == 0 && s->accuracy == 0)
		s->str[0] = '\0';
	if (s->accuracy > 0)
		ft_printf_data_d3(s);
	if (s->plus == 1 || s->spase == 1)
		ft_printf_data_ps(s);
	if (s->width > (int)ft_strlen(s->str))
		ft_printf_data_d2(s);
	if (s->width > 0 && s->width > (int)ft_strlen(s->str))
	{
		if (s->zero == 1 && (s->width <= s->accuracy ||
			s->accuracy < 1))
			ft_printf_data_width(s, '0');
		else
			ft_printf_data_width(s, ' ');
	}
	ft_strdel(&s->str);
}

void	ft_printf_data_d2(t_arg *s)
{
	s->l1 = 0;
	if ((s->str[0] == '+' || s->str[0] == '-' || s->str[0] == ' ')
		&& s->minus != 1 && s->zero == 1)
	{
		s->l3 = 0;
		s->l4 = 1;
		s->l1 = (int)s->str[0];
		s->tmp1 = ft_strnew(ft_strlen(s->str));
		while (s->str[s->l4])
			s->tmp1[s->l3++] = s->str[s->l4++];
		s->tmp1[s->l3] = '\0';
		free(s->str);
		s->str = s->tmp1;
	}
	while (s->width > (int)ft_strlen(s->str) && s->minus == 1)
		s->str = ft_strjoin(s->str, " \0");
	while (s->width > (int)ft_strlen(s->str) && s->minus != 1)
	{
		if (s->zero == 1)
			s->str = ft_strjoin("0\0", s->str);
		else
			s->str = ft_strjoin(" \0", s->str);
	}
	if (s->l1 != 0)
		s->str[0] = (char)s->l1;
}

void	ft_printf_data_d3(t_arg *s)
{
	if ((int)ft_strlen(s->str) > s->accuracy)
		return ;
	s->tmp1 = ft_strnew(ft_strlen(s->str));
	if (s->str[0] == '-')
		s->l1 = 1;
	else
		s->l1 = 0;
	s->l3 = 0;
	while (s->str[s->l1] != '\0')
		s->tmp1[s->l3++] = s->str[s->l1++];
	while ((int)ft_strlen(s->tmp1) < s->accuracy)
		s->tmp1 = ft_strjoin("0\0", s->tmp1);
	if (s->str[0] == '-')
		s->tmp1 = ft_strjoin("-\0", s->tmp1);
	free(s->str);
	s->str = s->tmp1;
	s->zero = 0;
}
