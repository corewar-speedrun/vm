/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 15:28:45 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/01 15:28:47 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int start;

	start = 0;
	while (s[start])
	{
		if (s[start] == (char)c)
			return ((char *)s + start);
		start++;
	}
	if (s[start] == (char)c)
		return ((char *)s + start);
	return (NULL);
}
