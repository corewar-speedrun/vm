/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_data_s_wchar_t.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 21:52:33 by dverbyts          #+#    #+#             */
/*   Updated: 2017/08/12 21:52:37 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_data_s_wchar_t(t_arg *s)
{
	int	len;

	if (s->buf != NULL)
	{
		ft_printf_data_wchar_read(s);
		len = ft_strlen(s->str);
	}
	else
		s->str = ft_strdup("(null)\0");
	if (s->spase == 1 && (s->buf != NULL && ft_strcmp(s->str, "(null)") != 0
		&& s->str[0] != '\0'))
		ft_printf_data_ps(s);
	if (s->width > 0 && s->width > len)
	{
		if (s->zero == 1)
			return (ft_printf_data_wchar_width(s, '0'));
		else
			return (ft_printf_data_wchar_width(s, ' '));
	}
	return ;
}

void	ft_printf_data_wchar_read(t_arg *s)
{
	if (s->accuracy > -1)
		return (ft_printf_data_wchar_read2(s));
	s->wchar = (wchar_t *)s->buf;
	s->tmp1 = ft_strnew(1);
	while (s->wchar[s->l3])
	{
		if ((int)s->wchar[s->l3] < 128)
		{
			s->tmp2 = ft_strnew(1);
			s->tmp2[0] = (char)s->wchar[s->l3++];
		}
		else
			s->tmp2 = ft_printf_wchar_decode((int)s->wchar[s->l3++], s, 0);
		s->tmp1 = ft_strjoin(s->tmp1, s->tmp2);
	}
	s->str = s->tmp1;
	return ;
}

void	ft_printf_data_wchar_read2(t_arg *s)
{
	s->wchar = (wchar_t *)s->buf;
	s->tmp1 = ft_strnew(1);
	while (s->wchar[s->l3] && (int)ft_strlen(s->tmp1) < s->accuracy)
	{
		if ((int)s->wchar[s->l3] < 128)
		{
			s->tmp2 = ft_strnew(1);
			s->tmp2[0] = (char)s->wchar[s->l3++];
		}
		else
			s->tmp2 = ft_printf_wchar_decode((int)s->wchar[s->l3++], s, 0);
		if (((int)ft_strlen(s->tmp1) + (int)ft_strlen(s->tmp2)) > s->accuracy)
		{
			if (s->tmp2)
				free(s->tmp2);
			break ;
		}
		s->tmp1 = ft_strjoin(s->tmp1, s->tmp2);
	}
	s->str = s->tmp1;
	return ;
}

void	ft_printf_data_wchar_width(t_arg *s, char t)
{
	char	*tmp;

	s->l4 = 0;
	s->l3 = ft_strlen(s->str);
	tmp = ft_strnew(s->l3);
	while (s->l3++ < s->width)
		tmp[s->l4++] = t;
	if (s->minus == 1)
		tmp = ft_strjoin(s->str, tmp);
	else
		tmp = ft_strjoin(tmp, s->str);
	s->str = tmp;
	return ;
}

char	*ft_printf_wchar_decode(int t, t_arg *s, int z)
{
	char	*ret;

	if (t < 2048)
		s->l4 = 1;
	else if (t < 65536)
		s->l4 = 2;
	else
		s->l4 = 3;
	ret = ft_strnew(s->l4 + 1);
	if (s->l4 == 1 || s->l4 == 2)
		z = s->l4 == 1 ? 192 : 224;
	else
		z = 240;
	s->l5 = 0;
	ret[s->l5++] = (char)(((t >> (6 * s->l4)) & 63) + z);
	if (s->l4 > 1)
		ret[s->l5++] = (char)(((t >> (6 * (s->l4 - 1))) & 63) + 128);
	if (s->l4 > 2)
		ret[s->l5++] = (char)(((t >> (6 * (s->l4 - 2))) & 63) + 128);
	ret[s->l5] = (char)((t & 63) + 128);
	return (ret);
}
