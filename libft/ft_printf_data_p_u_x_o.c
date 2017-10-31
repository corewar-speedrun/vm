/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_data_p_u_x_o.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 14:26:52 by dverbyts          #+#    #+#             */
/*   Updated: 2017/08/20 14:26:53 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_data_p(t_arg *s)
{
	s->ll = 1;
	s->str = ft_printf_itoa_unsigned(s, 16, 0);
	if ((ptrdiff_t)s->buf == 0 && s->accuracy == 0)
		s->str[0] = '\0';
	while ((int)ft_strlen(s->str) < s->accuracy)
		s->str = ft_strjoin("0\0", s->str);
	if (s->plus == 1)
		s->plus = 0;
	if (s->width > 0 && s->width > (int)ft_strlen(s->str))
	{
		if (s->zero == 1)
		{
			ft_printf_data_width(s, '0');
			return (ft_printf_data_0x(s));
		}
		else
		{
			ft_printf_data_0x(s);
			return (ft_printf_data_width(s, ' '));
		}
	}
	ft_printf_data_0x(s);
	return ;
}

void	ft_printf_data_u(t_arg *s)
{
	if (s->data == 'U')
		s->l = 1;
	s->str = ft_printf_itoa_unsigned(s, 10, 0);
	if ((unsigned long long)s->buf == 0 && s->accuracy == 0)
	{
		s->str[0] = '\0';
		return ;
	}
	if (s->plus == 1)
		s->plus = 0;
	while ((int)ft_strlen(s->str) < s->accuracy)
		s->str = ft_strjoin("0\0", s->str);
	if (s->width > 0 && s->width > (int)ft_strlen(s->str))
	{
		if (s->zero == 1)
			return (ft_printf_data_width(s, '0'));
		else
			return (ft_printf_data_width(s, ' '));
	}
	return ;
}

void	ft_printf_data_x(t_arg *s)
{
	s->str = ft_printf_itoa_unsigned(s, 16, 0);
	if ((unsigned long long)s->buf == 0 && s->accuracy == 0)
		s->str[0] = '\0';
	while ((int)ft_strlen(s->str) < s->accuracy)
		s->str = ft_strjoin("0\0", s->str);
	if (s->width <= 0 || (s->minus != 1 && s->zero != 1) || (s->minus == 1 &&
		s->zero == 1))
		ft_printf_data_0x(s);
	if (s->plus == 1)
		s->plus = 0;
	if (s->width > 0 && s->width > (int)ft_strlen(s->str))
	{
		if (s->zero == 1 && s->minus != 1)
		{
			ft_printf_data_width(s, '0');
			if (s->hash == 1)
				s->str[1] = s->data > 96 ? 'x' : 'X';
		}
		else
			ft_printf_data_width(s, ' ');
	}
	return ;
}

void	ft_printf_data_o(t_arg *s)
{
	if (s->data == 'O')
		s->l = 1;
	s->str = ft_printf_itoa_unsigned(s, 8, 0);
	if ((unsigned long long)s->buf == 0 && s->accuracy == 0)
	{
		if (s->hash == 1)
		{
			s->str[0] = '0';
			s->str[1] = '\0';
		}
		else
			s->str[0] = '\0';
		if (s->accuracy <= 0 && s->width < 1)
			return ;
	}
	if (s->plus == 1)
		s->plus = 0;
	if (s->hash == 1 && s->str[0] != '0')
		s->str = ft_strjoin("0\0", s->str);
	if (s->width > 0 || s->accuracy > -1)
		ft_printf_data_o2(s);
	return ;
}

void	ft_printf_data_o2(t_arg *s)
{
	char	*ss;

	if (s->accuracy > -1 && s->accuracy > (int)ft_strlen(s->str))
	{
		s->l1 = s->accuracy - (int)ft_strlen(s->str);
		s->l4 = 0;
		ss = ft_strnew(s->l1);
		while (s->l4 < s->l1)
			ss[s->l4++] = '0';
		ss[s->l4] = '\0';
		s->str = ft_strjoin(ss, s->str);
	}
	if (s->width > 0 && s->width > (int)ft_strlen(s->str))
	{
		if (s->zero == 1 && s->minus != 1)
			return (ft_printf_data_width(s, '0'));
		else
			return (ft_printf_data_width(s, ' '));
	}
	return ;
}
