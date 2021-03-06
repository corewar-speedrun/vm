/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 18:03:17 by dverbyts          #+#    #+#             */
/*   Updated: 2016/11/25 18:03:19 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int z;
	int x;

	z = ft_strlenint(s1);
	x = 0;
	while (s2[x])
		s1[z++] = s2[x++];
	s1[z] = '\0';
	return (s1);
}
