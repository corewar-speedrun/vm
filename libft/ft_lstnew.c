/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 18:18:48 by dverbyts          #+#    #+#             */
/*   Updated: 2016/12/16 18:18:49 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *re;

	if (!(re = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		re->content = NULL;
		re->content_size = 0;
		re->next = NULL;
	}
	else
	{
		if (!(re->content = malloc(content_size)))
			return (0);
		ft_memcpy(re->content, content, content_size);
		re->content_size = content_size;
		re->next = NULL;
	}
	return (re);
}
