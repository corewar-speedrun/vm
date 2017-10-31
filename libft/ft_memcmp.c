/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 21:16:48 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/02 21:16:49 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				start;
	const unsigned char	*dest;
	const unsigned char	*sors;

	dest = s1;
	sors = s2;
	start = 0;
	while (n--)
	{
		if (dest[start] == sors[start])
			start++;
		else
			return (dest[start] - sors[start]);
	}
	return (0);
}
