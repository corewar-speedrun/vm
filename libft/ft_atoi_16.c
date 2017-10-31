/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 17:17:14 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/05 17:17:15 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_hex(char *str)
{
	int		r;

	r = 0;
	if (*str > 64 && *str < 71)
		r = (*str * 1 - 55);
	else
		r = (*str * 1 - 87);
	return (r);
}

int		if_neg(char *s)
{
	int		i;

	i = 1;
	if ((*s == '+' || *s == '-') && (((*s + i) > 47 && (*s + i) < 58) ||
		((*s + i) > 64 && (*s + i) < 71) || ((*s + i) > 96 && (*s + i) < 103)))
		return (1);
	return (0);
}

int		ft_atoi_16(char *str)
{
	unsigned long int	rez;
	int					neg;
	int					i;

	i = 0;
	rez = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' ||
		*str == '\v' || *str == '\r' || *str == '\f')
		str++;
	neg = (*str == '-') ? -1 : 1;
	if ((*str == '-' || *str == '+') && if_neg(str++) == 0)
		return (0);
	while ((*str > 47 && *str < 58) || (*str > 64 && *str < 71) ||
		(*str > 96 && *str < 103))
	{
		if (ft_isdigit(*str) == 1)
			rez = rez * 16 + (*str * 1 - 48);
		else
			rez = rez * 16 + is_hex(str);
		str++;
		i++;
	}
	return ((int)(rez * neg));
}
