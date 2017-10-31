/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 23:08:12 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/02 23:08:14 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, int c)
{
	size_t start;

	start = ft_strlen(s);
	while (s[start] != (char)c && start > 0)
		start--;
	if (s[start] == (char)c)
		return ((char *)s + start);
	return (NULL);
}
