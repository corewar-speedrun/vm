/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaznyts <dmaznyts@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 17:03:13 by dmaznyts          #+#    #+#             */
/*   Updated: 2017/10/24 17:28:15 by dmaznyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nl(int value, int base)
{
	int	i;

	i = 0;
	while (value <= -base || value >= base)
	{
		i++;
		value /= base;
	}
	i++;
	return (i);
}

char		*ft_itoa_base(int value, int base)
{
	char	*tmp;
	int		i;
	int		l;
	char	*str;

	tmp = "0123456789abcdef";
	i = 0;
	l = nl(value, base);
	if (base < 2 || base > 16 || !(str = ft_strnew(l)))
		return (0);
	str[l] = '\0';
	if (base == 10 && value < 0)
		str[i++] = '-';
	else
		l--;
	while (l >= i)
	{
		str[l] = tmp[(value % base) < 0 ? -(value % base) : (value % base)];
		l--;
		value /= base;
	}
	return (str);
}
