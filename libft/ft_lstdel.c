/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 16:26:06 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/19 16:26:08 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del) (void *, size_t))
{
	t_list *buf;

	if (!*alst && !alst)
		return ;
	while (*alst)
	{
		buf = (*alst)->next;
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = buf;
	}
	*alst = NULL;
}
