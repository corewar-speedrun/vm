/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 19:31:40 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/13 19:31:41 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *t, char *y)
{
	char	*r;
	int		i;
	int		x;

	if (!t || !y)
		return (0);
	if (!(r = (char *)malloc(sizeof(char) * (ft_strlen(t) + ft_strlen(y) + 1))))
		return (0);
	i = 0;
	x = 0;
	while (t[i])
		r[x++] = t[i++];
	i = 0;
	while (y[i])
		r[x++] = y[i++];
	r[x] = '\0';
	return (r);
}
