/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 16:10:49 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/13 16:10:52 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		len(int n)
{
	int len;

	len = 1;
	if (n <= 0)
	{
		n = n * -1;
		len++;
	}
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char		*rev(char *src, char *dst, int s, int min)
{
	int d;
	int count;

	count = ft_strlen(src) - 1;
	d = 0;
	if (min == 1)
	{
		dst[d] = '-';
		d++;
		s--;
	}
	while (s)
	{
		dst[d] = src[count];
		d++;
		s--;
		count--;
	}
	if (src[0] == 0)
		dst[0] = '0';
	dst[d] = '\0';
	return (dst);
}

static char		*make(unsigned int n, char *r, int minf, int l)
{
	char	*buf;
	int		count;
	int		y;

	count = len(n) - 1;
	y = len(n);
	if (!(buf = (char*)malloc(sizeof(char) * y)))
		return (0);
	if (minf == 1)
	{
		n = n * -1;
		count--;
	}
	while (l < count)
	{
		buf[l] = n % 10 + '0';
		n = n / 10;
		l++;
	}
	buf[l] = '\0';
	r = rev(buf, r, --y, minf);
	if (!buf)
		return (r);
	free(buf);
	return (r);
}

char			*ft_itoa(int n)
{
	int				minf;
	char			*re;
	unsigned int	x;
	int				size;

	minf = 0;
	x = n;
	if (n < 0)
		minf = 1;
	size = len(n);
	if (!(re = (char*)malloc(sizeof(char) * size)))
		return (0);
	re = make(x, (char *)re, minf, 0);
	return (re);
}
