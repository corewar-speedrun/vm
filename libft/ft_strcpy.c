/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 16:52:29 by dverbyts          #+#    #+#             */
/*   Updated: 2016/11/21 16:52:32 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *sors)
{
	size_t	start;
	size_t	end;

	end = ft_strlen(sors);
	start = 0;
	while (end)
	{
		dest[start] = sors[start];
		end--;
		start++;
	}
	dest[start] = '\0';
	return (dest);
}
