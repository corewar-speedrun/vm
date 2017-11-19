/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 18:16:39 by dverbyts          #+#    #+#             */
/*   Updated: 2016/11/24 18:16:40 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	int	z;
	int rez;

	if (!s1 || !s2 || ft_strlen(s1) != ft_strlen(s2))
		return (0);
	if (s1[0] == s2[0])
		rez = 1;
	else
		return (0);
	z = -1;
	while (s1[++z])
	{
		if (s1[z] == s2[z])
			rez = 1;
		else
			return (0);
	}
	return (rez);
}
