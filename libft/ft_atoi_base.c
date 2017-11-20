/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 19:46:00 by dverbyts          #+#    #+#             */
/*   Updated: 2017/10/31 19:46:02 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	test_base(char nb)
{
	if (nb >= '0' && nb <= '9')
		return (nb - '0');
	else if (nb >= 'a' && nb <= 'z')
		return (nb - 'a' + 10);
	else if (nb >= 'A' && nb <= 'Z')
		return (nb - 'A' + 10);
	else
		return (-1);
}

int	ft_atoi_base(unsigned char *str, int str_base)
{
	int temp;
	int value;
	int sign;

	value = 0;
	sign = 1;
	if (str_base < 2 || str_base > 16 || (!str))
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\f' ||
			*str == '\v' || *str == '\n' || *str == '\r')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	temp = test_base(*str);
	while (temp >= 0 && temp <= str_base)
	{
		value = value * str_base + temp;
		str++;
		temp = test_base(*str);
	}
	return (value * sign);
}
