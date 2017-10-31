/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 19:32:09 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/02 19:32:11 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	int start;

	start = 0;
	while (n--)
	{
		((unsigned char *)dst)[start] = ((unsigned char *)src)[start];
		if (((unsigned char *)src)[start] == (unsigned char)c)
			return ((unsigned char *)dst + ++start);
		start++;
	}
	return (NULL);
}
