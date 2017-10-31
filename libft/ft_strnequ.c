/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 19:17:19 by dverbyts          #+#    #+#             */
/*   Updated: 2016/11/24 19:17:21 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	z;
	int		rez;

	if (!s1 || !s2)
		return (0);
	if (!n)
		return (1);
	rez = 0;
	if (s1[0] == s2[0])
		rez = 1;
	else
		return (0);
	z = 0;
	while ((z + 1) < n && s1[z++])
	{
		if (s1[z] == s2[z])
			rez = 1;
		else
			return (0);
	}
	return (rez);
}
