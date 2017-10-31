/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_data_c.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 21:15:13 by dverbyts          #+#    #+#             */
/*   Updated: 2017/08/15 21:15:15 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_data_s(t_arg *s)
{
	if (s->l == 1 || s->data == 'S')
		return (ft_printf_data_s_wchar_t(s));
	else
	{
		if (s->buf != NULL)
			s->str = ft_strdup((char *)s->buf);
		else
			s->str = ft_strdup("(null)\0");
	}
	if (s->spase == 1 && (s->buf != NULL && ft_strcmp(s->str, "(null)") != 0
		&& s->str[0] != '\0'))
		ft_printf_data_ps(s);
	if (s->accuracy > -1 && s->accuracy < (int)ft_strlen(s->str))
		s->str[s->accuracy] = '\0';
	if (s->width > 0 && s->width > (int)ft_strlen(s->str))
	{
		if (s->zero == 1 && s->minus != 1)
			return (ft_printf_data_width(s, '0'));
		else
			return (ft_printf_data_width(s, ' '));
	}
	return ;
}

void	ft_printf_data_c(t_arg *s)
{
	if (s->l == 1 || s->data == 'C')
		return (ft_printf_data_c_wchar_t(s));
	s->str = ft_strnew(1);
	if (s->buf != NULL)
		s->str[0] = (char)s->buf;
	else
		s->str[0] = '\0';
	if (s->str[0] == '\0')
		s->buf = NULL;
	if (s->str[0] == '\0' && s->width > 1 && s->minus == 1)
		return (ft_printf_data_c2(s));
	if (s->width > 1)
	{
		s->zero == 1 ? ft_printf_data_width_c(s, '0') :
		ft_printf_data_width_c(s, ' ');
	}
	return ;
}

void	ft_printf_data_c2(t_arg *s)
{
	char *tmp;

	write(1, &s->str[0], 1);
	s->re++;
	s->l1 = 0;
	s->l3 = (int)ft_strlen(s->str);
	s->l4 = s->width - s->l3 - (s->buf == NULL ? 1 : 0);
	tmp = ft_strnew(s->l3 + s->l4);
	if (s->minus == 1)
	{
		while (s->l5 < s->l4 && s->str[s->l1] != '\0')
			tmp[s->l5++] = s->str[s->l1++];
		while (s->l5 < (s->l3 + s->l4))
			tmp[s->l5++] = ' ';
	}
	else
	{
		while (s->l5 < s->l4)
			tmp[s->l5++] = (s->zero == 1 ? '0' : ' ');
		while (s->l5 < (s->l3 + s->l4) && s->str[s->l1] != '\0')
			tmp[s->l5++] = s->str[s->l1++];
	}
	tmp[s->l5] = '\0';
	s->str = tmp;
	s->data = 's';
}

void	ft_printf_data_c_wchar_t(t_arg *s)
{
	wchar_t wchar;

	if (s->buf != NULL)
	{
		wchar = (wchar_t)s->buf;
		if ((int)wchar < 128)
		{
			s->str = ft_strnew(1);
			s->str[0] = (char)wchar;
		}
		else
			s->str = ft_printf_wchar_decode((int)wchar, s, 0);
	}
	else
		s->str = ft_strdup("\0");
	if (s->width > 1)
	{
		if (s->zero == 1)
			return (ft_printf_data_wchar_width(s, '0'));
		else
			return (ft_printf_data_wchar_width(s, ' '));
	}
	return ;
}

void	ft_printf_data_width_c(t_arg *s, char t)
{
	char *tmp;

	s->l1 = 0;
	s->l3 = (int)ft_strlen(s->str);
	s->l4 = s->width - s->l3 - (s->buf == NULL ? 1 : 0);
	tmp = ft_strnew(s->l3 + s->l4);
	if (s->minus == 1)
	{
		while (s->l5 < s->l4 && s->str[s->l1] != '\0')
			tmp[s->l5++] = s->str[s->l1++];
		while (s->l5 < (s->l3 + s->l4))
			tmp[s->l5++] = t;
	}
	else
	{
		while (s->l5 < s->l4)
			tmp[s->l5++] = t;
		while (s->l5 < (s->l3 + s->l4) && s->str[s->l1] != '\0')
			tmp[s->l5++] = s->str[s->l1++];
	}
	tmp[s->l5] = '\0';
	free(s->str);
	s->str = tmp;
	return ;
}
