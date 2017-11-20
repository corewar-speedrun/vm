/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaznyts <dmaznyts@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 09:57:40 by dmaznyts          #+#    #+#             */
/*   Updated: 2017/11/20 09:59:41 by dmaznyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				vm_read_flag2(char *str)
{
	char *str2;

	if (g_vm->error == 2)
		g_vm->error = -1;
	str2 = str;
	while (*str2)
	{
		if (ft_isdigit(*str2))
			str2++;
		else
		{
			g_vm->error = 8;
			return (0);
		}
	}
	g_vm->damp = ft_atoi(str);
	if (g_vm->damp < 1)
		g_vm->error = 10;
	return (0);
}

t_champ			*vm_parsing(int fd)
{
	t_champ			*tmp;
	unsigned char	buf[10];

	if (!(tmp = (t_champ *)malloc(sizeof(t_champ) * 1)))
		return (NULL);
	ft_bzero(tmp, sizeof(t_champ));
	if (g_vm->error == -1)
		tmp->name = (char *)vm_read_script(PROG_NAME_LENGTH + 4, fd, 1);
	if (g_vm->error == -1)
		tmp->size = vm_read_size(4, fd);
	if (g_vm->error == -1)
		tmp->comment = (char *)vm_read_script(COMMENT_LENGTH + 4, fd, 1);
	if (g_vm->error == -1 && tmp->size <= (MEM_SIZE / 6))
		tmp->src = vm_read_script(tmp->size, fd, 0);
	if (g_vm->error == -1)
		tmp->nmbr = g_vm->champs_nmbr + 1;
	else if (g_vm->error == -1)
		g_vm->error = 4;
	if (read(fd, &buf, 10) != 0)
		g_vm->error = 6;
	return (tmp);
}

/*
** vm_parsing - малочим память под чемпиона и парсим в нее чемпиона
**
** tmp->name - имя чемпиона. кащу к char.
** tmp->size - размер рабочего кода чемпиона. считываю согласно этого размера и
** на поле размещать исходя из этого значения. перевожу в инт через атои_бейс.
** tmp->comment - комент. в оригинальной ВМ без визуализатора выводится, с
** визуализатором не используется. у нас должно выводится dвезде. кащу в char.
** tmp->src - исходный код чемпиона. размещается на игровом поле.
*/
