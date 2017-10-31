/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_split_format.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 21:12:58 by dverbyts          #+#    #+#             */
/*   Updated: 2017/08/01 21:13:00 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		how_m_words(char const *str)
{
	int		words;
	int		i;
	int		f;

	words = 1;
	i = 0;
	f = 0;
	while (str[i])
	{
		if (str[i] == '%' && f == 0)
			f++;
		else if (ft_printf_chek_data(str[i]) == 1 && f == 1)
		{
			words++;
			f = 0;
		}
		i++;
	}
	return (words);
}

int		how_b(char const *s, int i)
{
	int		counter;

	counter = 1;
	while (s[i] == '%' && s[i++] != '\0')
		counter++;
	while (s[i] != '\0' && ft_printf_chek_data(s[i++]) != 1)
		counter++;
	while (s[i] != '%' && s[i++] != '\0')
		counter++;
	if (ft_printf_chek_data(s[i++]) == 1)
		counter++;
	return (counter);
}

char	**ft_printf_split_format(char const *f, int i, int args, int a)
{
	char	**array;
	int		l;
	int		arg;

	if (!f)
		return (NULL);
	args = how_m_words(f);
	array = (char **)malloc(sizeof(char *) * args);
	ft_bzero(array, sizeof(char *) * args);
	while (f[a] != '\0')
	{
		arg = how_b(f, a);
		l = 0;
		array[i] = (char *)malloc(sizeof(char) * arg + 1);
		ft_bzero(array[i], sizeof(char) * arg);
		while ((f[a] == '%') && f[a] != '\0')
			array[i][l++] = f[a++];
		while (f[a] != '\0' && ft_printf_chek_data(f[a - 1]) != 1)
			array[i][l++] = f[a++];
		while (f[a] != '%' && f[a] != '\0')
			array[i][l++] = f[a++];
		array[i++][arg] = '\0';
	}
	array[i] = NULL;
	return (array);
}

int		ft_printf_chek_data(char f)
{
	if (f == 's' || f == 'S' || f == 'p' || f == 'd' || f == 'D' || f == 'i'
		|| f == 'o' || f == 'O' || f == 'u' || f == 'U' || f == 'x' || f == 'X'
		|| f == 'c' || f == 'C' || f == 'n')
		return (1);
	return (0);
}
