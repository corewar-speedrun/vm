/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 21:09:08 by dverbyts          #+#    #+#             */
/*   Updated: 2016/11/24 21:09:09 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *sors, size_t n)
{
	size_t s;

	s = 0;
	while (s < n)
	{
		dest[s] = sors[s];
		if (sors[s] == '\0')
		{
			while (s < n)
			{
				dest[s] = '\0';
				s++;
			}
			return (dest);
		}
		s++;
	}
	return (dest);
}
