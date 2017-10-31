/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 16:43:41 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/21 16:43:43 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush(t_list *current, void *content, size_t content_size)
{
	size_t i;

	i = 0;
	while (current->next != NULL)
	{
		i++;
		current = current->next;
	}
	if (!(current->next = (t_list *)malloc(sizeof(t_list))))
		return ;
	if (!(current->next->content = malloc(content_size)))
		return ;
	ft_memcpy(current->next->content, content, content_size);
	current->next->content_size = content_size;
	current->next->next = NULL;
}
