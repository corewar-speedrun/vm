/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 19:07:45 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/13 19:07:47 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*re;
	size_t	i;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (0);
	if (!(re = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while (i < len)
	{
		re[i] = s[start];
		i++;
		start++;
	}
	re[i] = '\0';
	return (re);
}
