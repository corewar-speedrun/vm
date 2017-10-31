/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:47:30 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/15 16:47:32 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f) (char))
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
		array[z] = f(s[z]);
		z++;
	}
	array[z] = '\0';
	return (array);
}
