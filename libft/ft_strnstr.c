/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 23:19:19 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/02 23:19:20 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *ltl, size_t len)
{
	size_t	len2;

	if (ltl[0] == '\0')
		return ((char *)big);
	len2 = ft_strlen(ltl);
	while (*big && len-- >= len2)
	{
		if (*big == *ltl && ft_memcmp(big, ltl, len2) == 0)
			return ((char *)big);
		big++;
	}
	return (NULL);
}
