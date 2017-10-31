/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 16:09:11 by dverbyts          #+#    #+#             */
/*   Updated: 2017/02/25 16:09:13 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_next_line(const int fd, char **line)
{
	static t_line	*start = NULL;
	t_line			*buf;

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (start == NULL)
		start = make_list(fd);
	buf = start;
	while (buf != NULL && buf->n_fd != fd)
	{
		if (buf->next == NULL && buf->n_fd != fd)
			buf->next = make_list(fd);
		buf = buf->next;
	}
	if (read_file(&buf, fd) == -1)
		return (-1);
	if (buf->l[0] != '\0')
	{
		*line = string(&buf);
		return (1);
	}
	return (0);
}

int		read_file(t_line **lst, int fd)
{
	t_line	*buf;
	char	b[BUFF_SIZE + 1];
	char	*tmp;
	ssize_t	ret;

	ret = 0;
	buf = *lst;
	while ((ret = read(fd, b, BUFF_SIZE)) > 0)
	{
		b[ret] = '\0';
		tmp = ft_strjoin(buf->l, b);
		ft_strdel(&buf->l);
		buf->l = tmp;
		if (ft_strrchr(b, 10) != NULL)
			break ;
	}
	if (ret <= 0 && tmp == NULL)
		return (ret == -1 ? -1 : 0);
	return (1);
}

t_line	*make_list(int fd)
{
	t_line	*ln;

	if (!(ln = (t_line *)malloc(sizeof(t_line) * 1)))
		return (NULL);
	ln->l = ft_strdup("\0");
	ln->n_fd = fd;
	ln->next = NULL;
	return (ln);
}

char	*string(t_line **tmp)
{
	char	*str;
	char	*src;
	t_line	*ptr;
	ssize_t	len;
	ssize_t	i;

	i = 0;
	ptr = *tmp;
	while (ptr->l[i] != '\n' && ptr->l[i] != '\0')
		i++;
	len = ft_strlen(ptr->l);
	str = ft_strsub(ptr->l, 0, i);
	if (len == i)
		src = ft_strnew(0);
	else
		src = ft_strsub(ptr->l, i + 1, len - i - 1);
	if (*(ptr->l) != '\0')
		ft_memdel((void *)&ptr->l);
	ptr->l = src;
	return (str);
}
