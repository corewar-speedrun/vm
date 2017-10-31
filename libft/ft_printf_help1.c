/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_help1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 15:28:21 by dverbyts          #+#    #+#             */
/*   Updated: 2017/09/05 15:28:24 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_data_ps(t_arg *s)
{
	char t[2];

	t[0] = '\0';
	t[1] = '\0';
	if (s->spase == 1 && (s->str[0] != '-' && s->str[0] != '+'))
		t[0] = ' ';
	if (s->plus == 1)
	{
		if (s->str[0] == '-')
			t[0] = '-';
		else
			t[0] = '+';
	}
	if (t[0] != s->str[0])
		s->str = ft_strjoin(t, s->str);
	return ;
}

void	ft_printf_data_width(t_arg *s, char t)
{
	char *tmp;

	s->l1 = 0;
	s->l3 = (int)ft_strlen(s->str);
	s->l4 = s->width - s->l3;
	tmp = ft_strnew(s->l3 + s->l4);
	if (s->minus == 1)
	{
		while (s->l5 < s->l3 && s->str[s->l1] != '\0')
			tmp[s->l5++] = s->str[s->l1++];
		while (s->l5 < (s->l3 + s->l4))
			tmp[s->l5++] = t;
	}
	else
	{
		while (s->l5 < s->l4)
			tmp[s->l5++] = t;
		while (s->l5 < (s->l3 + s->l4) && s->str[s->l1] != '\0')
			tmp[s->l5++] = s->str[s->l1++];
	}
	tmp[s->l5] = '\0';
	free(s->str);
	s->str = tmp;
	return ;
}

void	ft_printf_data_0x(t_arg *s)
{
	if (((s->data != 'x' && s->data != 'X') || s->hash != 1 ||
		(unsigned long long)s->buf == 0) && s->data != 'p')
		return ;
	if (s->width && (int)ft_strlen(s->str) == s->width && s->buf == NULL)
	{
		if (s->data > 96)
			s->str[1] = 'x';
		else
			s->str[1] = 'X';
		return ;
	}
	if (s->data > 96)
		s->str = ft_strjoin("0x", s->str);
	else
		s->str = ft_strjoin("0X", s->str);
}

int		ft_printf_data_type2(char f)
{
	if (f == 's' || f == 'S' || f == 'p' || f == 'd' || f == 'D' || f == 'i'
		|| f == 'o' || f == 'O' || f == 'u' || f == 'U' || f == 'x' || f == 'X'
		|| f == 'c' || f == 'C' || f == 'n')
		return (1);
	return (0);
}

void	ft_printf_data_ss(char p, char *y, t_arg *s)
{
	int i;

	i = 0;
	if (p && y == NULL)
	{
		write(1, &p, 1);
		s->re++;
		return ;
	}
	if (y != NULL)
	{
		while (y[i])
		{
			write(1, &y[i++], 1);
			s->re++;
		}
		return ;
	}
}
