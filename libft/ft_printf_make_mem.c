/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_make_mem.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 17:29:11 by dverbyts          #+#    #+#             */
/*   Updated: 2017/08/01 17:29:13 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_arg	*ft_printf_make_mem(void)
{
	t_arg *ret;

	if (!(ret = (t_arg *)malloc(sizeof(t_arg))))
		return (0);
	ft_bzero(ret, sizeof(t_arg));
	ret->accuracy = -1;
	return (ret);
}

void	ft_printf_clear_t_arg2(t_arg *s)
{
	s->hh = 0;
	s->h = 0;
	s->l = 0;
	s->ll = 0;
	s->j = 0;
	s->z = 0;
	s->t = 0;
	s->lll = 0;
	s->prs = 0;
	s->accuracy = -1;
	s->width = 0;
	s->minus = 0;
	s->plus = 0;
	s->spase = 0;
	s->hash = 0;
	s->zero = 0;
	s->str = 0;
	s->buf = 0;
	s->data = 0;
	s->l1 = 0;
	s->l3 = 0;
	s->l4 = 0;
	s->l5 = 0;
	return ;
}

void	ft_printf_clear_t_arg(t_arg *s)
{
	s->l2 = 0;
	s->j1 = 0;
	s->j2 = 0;
	s->j3 = 0;
	s->j4 = 0;
	s->j5 = 0;
	s->j6 = 0;
	s->wchar = 0;
	s->tmp1 = 0;
	s->tmp2 = 0;
	ft_printf_clear_t_arg2(s);
	return ;
}

void	ft_printf_del_arg(t_arg *del)
{
	int l;

	l = 0;
	if (del != NULL)
	{
		while (del->arg[l])
			free(del->arg[l++]);
		free(del->arg);
		free(del);
	}
	return ;
}
