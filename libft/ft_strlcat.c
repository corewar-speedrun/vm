/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:31:19 by dverbyts          #+#    #+#             */
/*   Updated: 2016/11/28 18:31:20 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t s1;
	size_t s2;
	size_t size_n;

	s1 = ft_strlen(dst);
	if (s1 > size)
		s1 = size;
	size_n = s1;
	s2 = 0;
	while (src[s2] && s1 < size - 1)
	{
		dst[s1] = src[s2];
		s1++;
		s2++;
	}
	if (size_n < size)
		dst[s1] = '\0';
	return (size_n + ft_strlen(src));
}
