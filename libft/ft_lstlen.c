/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 17:22:36 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/21 17:22:37 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstlen(t_list *lst)
{
	size_t len;

	if (!lst)
		return (0);
	len = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		len++;
	}
	return ((int)len);
}
