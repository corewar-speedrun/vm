/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 12:20:11 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/16 12:20:13 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	char	*array;
	size_t	z;

	if (!s || !f)
		return (0);
	z = 0;
	if (!(array = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (s[z])
	{
		array[z] = f(z, s[z]);
		z++;
	}
	array[z] = '\0';
	return (array);
}
