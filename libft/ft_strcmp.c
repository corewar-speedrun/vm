/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 16:19:51 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/01 16:19:53 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char const *s1, char const *s2)
{
	int start;

	start = 0;
	while ((s1[start] == s2[start]) && (s1[start] != '\0') &&
		(s2[start] != '\0'))
		start++;
	return ((unsigned char)s1[start] - (unsigned char)s2[start]);
}
