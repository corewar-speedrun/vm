/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 16:41:25 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/19 16:41:27 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *curent, t_list *(*f) (t_list *elem))
{
	t_list *list_start;
	t_list *ggg;

	if (!curent || !f)
		return (NULL);
	list_start = f(curent);
	ggg = list_start;
	curent = curent->next;
	while (curent != NULL)
	{
		if (!(ggg->next = f(curent)))
			return (NULL);
		ggg = ggg->next;
		curent = curent->next;
	}
	return (list_start);
}
