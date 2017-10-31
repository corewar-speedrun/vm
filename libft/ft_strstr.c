/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 23:19:08 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/02 23:19:09 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *ltl)
{
	if (ltl[0] == '\0' || !ltl)
		return ((char *)big);
	while (*big)
	{
		if (*big == *ltl && ft_memcmp(big, ltl, ft_strlen(ltl)) == 0)
			return ((char *)big);
		big++;
	}
	return (NULL);
}
