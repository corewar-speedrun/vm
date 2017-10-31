/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_parsing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 17:41:14 by dverbyts          #+#    #+#             */
/*   Updated: 2017/08/05 17:41:15 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_printf_flags(char f, t_arg *s)
{
	if (f == '-')
		return (s->minus = 1);
	else if (f == '+')
		return (s->plus = 1);
	else if (f == ' ')
		return (s->spase = 1);
	else if (f == '#')
		return (s->hash = 1);
	else if (f == '0')
		return (s->zero = 1);
	return (0);
}

void	ft_printf_accuracy(char *f, t_arg *s, va_list args)
{
	if (f[s->l2] == '.')
		s->l2++;
	if (f[s->l2] == '*')
	{
		s->accuracy = va_arg(args, int);
		s->l2++;
	}
	else if (ft_isdigit(f[s->l2]) == 1)
	{
		s->accuracy = 0;
		while (ft_isdigit(f[s->l2]) == 1)
			s->accuracy = s->accuracy * 10 + (f[s->l2++] - '0');
	}
	if (s->accuracy == -1)
		s->accuracy = 0;
	return ;
}

void	ft_printf_width(char *f, t_arg *s, va_list args)
{
	s->width = 0;
	if (f[s->l2] == '*')
	{
		s->width = va_arg(args, int);
		s->l2++;
		if (s->width < 0)
		{
			s->minus = 1;
			s->width *= -1;
		}
	}
	else if (ft_isdigit(f[s->l2]) == 1)
		while (ft_isdigit(f[s->l2]) == 1)
			s->width = s->width * 10 + (f[s->l2++] - '0');
	if (s->width < 0)
	{
		s->minus = 1;
		s->width *= -1;
	}
	return ;
}

int		ft_printf_mods(char *f, t_arg *s)
{
	if (f[s->l2] == 'h' && s->h != 1)
		return (s->h = 1);
	else if (f[s->l2] == 'h' && s->h == 1)
	{
		s->h = 0;
		return (s->hh = 1);
	}
	else if (f[s->l2] == 'l' && s->l != 1)
		return (s->l = 1);
	else if (f[s->l2] == 'l' && s->l == 1)
	{
		s->l = 0;
		return (s->ll = 1);
	}
	else if (f[s->l2] == 'L')
		return (s->lll = 1);
	else if (f[s->l2] == 'j')
		return (s->j = 1);
	else if (f[s->l2] == 'z')
		return (s->z = 1);
	else if (f[s->l2] == 't')
		return (s->t = 1);
	return (0);
}
