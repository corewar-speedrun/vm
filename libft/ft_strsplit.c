/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 20:16:19 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/06 20:16:22 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		how_many_words(char const *str, char o)
{
	int words;
	int i;

	words = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != o && (str[i + 1] == o || str[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static int		how_big(char const *str, char z, int i)
{
	int counter;

	counter = 0;
	while (str[i] != z && str[i] != '\0')
	{
		counter++;
		i++;
	}
	return (counter);
}

static char		*copy(char *string, char const *str, char s, int count)
{
	int f;

	f = 0;
	while (str[count] != s && str[count] != '\0')
	{
		string[f] = str[count];
		f++;
		count++;
	}
	string[f] = '\0';
	return (string);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**array;
	int		i;
	int		a;

	if (!s || !c)
		return (0);
	if (!(array = (char **)malloc(sizeof(char *) * (how_many_words(s, c) + 1))))
		return (NULL);
	i = 0;
	a = 0;
	while (i < how_many_words(s, c))
	{
		while (s[a] == c && s[a])
			a++;
		if (!(array[i] = (char *)malloc(sizeof(char) * (how_big(s, c, a) + 1))))
			return (NULL);
		array[i] = copy(array[i], s, c, a);
		while (s[a] != c && s[a])
			a++;
		i++;
	}
	array[i] = 0;
	return (array);
}
