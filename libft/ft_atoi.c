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

int	ft_atoi(char *str)
{
	long long	rez;
	int			neg;

	rez = 0;
	neg = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' ||
		*str == '\v' || *str == '\r' || *str == '\f')
		str++;
	if (*str == '-')
		neg = -1;
	if ((*str == '+' && (ft_isdigit(*++str) != 1)) ||
	(*str == '-' && (ft_isdigit(*++str) != 1)))
		return (0);
	while (ft_isdigit(*str) == 1)
	{
		if ((rez > 922337203685477580 || (rez == 922337203685477580
			&& (*str - '0') > 7)) && neg == 1)
			return (-1);
		else if ((rez > 922337203685477580 || (rez == 922337203685477580
			&& (*str - '0') > 8)) && neg == -1)
			return (0);
		rez = (rez * 10 + *str * 1 - 48);
		str++;
	}
	return ((size_t)(rez * neg));
}
