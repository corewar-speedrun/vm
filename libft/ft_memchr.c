/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 21:04:30 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/02 21:04:31 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int start;

	start = 0;
	while (n--)
	{
		if (((unsigned char*)s)[start] == (unsigned char)c)
			return ((unsigned char*)s + start);
		start++;
	}
	return (NULL);
}
