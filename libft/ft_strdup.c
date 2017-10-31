/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 18:40:43 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/01 18:40:57 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *s2;

	s2 = malloc(sizeof(char) * (ft_strlenint(s1) + 1));
	if (!s2)
		return (NULL);
	return (ft_strcpy(s2, s1));
}
