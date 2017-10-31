/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 16:20:01 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/01 16:20:02 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	size_t start;

	if (!n)
		return (0);
	start = 0;
	while ((start + 1) < n && (s1[start] == s2[start]) && (s1[start] != '\0') &&
		(s2[start] != '\0'))
		start++;
	return ((unsigned char)s1[start] - (unsigned char)s2[start]);
}
