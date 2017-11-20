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

/*
** vm_read_flag - работа с флагами. Закодить.
*/

int				vm_read_flag(char *str)
{
	if (g_vm->error == 2)
		g_vm->error = -1;
	if (ft_strequ(str, "-l\0"))
		g_vm->flag_say_alive = 1;
	else if (ft_strequ(str, "-v\0"))
		g_vm->flag_visualize = 1;
	else if (ft_strequ(str, "-n\0"))
		return (2);
	else if (ft_strequ(str, "-damp\0"))
		return (1);
	else
		g_vm->error = 8;
	return (0);
}

int				vm_read_flag2(int i, char **arg, int x, int flag)
{
	char	*str;

	if (g_vm->error == 2)
		g_vm->error = -1;
	if (flag == 2)
		return (vm_read_flag3(i, arg, x, 0));
	str = arg[x];
	while (*str)
	{
		if (ft_isdigit(*str))
			str++;
		else
		{
			g_vm->error = 8;
			return (0);
		}
	}
	g_vm->damp = ft_atoi(arg[x]);
	if (g_vm->damp < 1)
		g_vm->error = 10;
	return (0);
}

int				vm_read_flag3(int i, char **arg, int x, int fd)
{
	t_champ	*tmp;
	char	*str;

	tmp = NULL;
	if (((x + 1) >= i || (fd = open(arg[x + 1], O_RDONLY)) == -1 ||
		vm_read_magic(fd, 0) != 1 || (tmp = vm_parsing(fd)) == NULL ||
			g_vm->error != -1 || (g_vm->namber + 1) > 4))
	{
		(fd > 0) ? close(fd) : 0;
		(tmp != NULL) ? free(tmp) : 0;
		g_vm->error = 8;
		return (0);
	}
	(fd > 0) ? close(fd) : 0;
	(tmp != NULL) ? free(tmp) : 0;
	str = arg[x];
	while (*str && g_vm->error == -1)
	{
		if (ft_isdigit(*str))
			str++;
		else
			g_vm->error = 8;
	}
	return ((g_vm->error == -1) ? vm_read_flag4(arg, x) : 0);
}

int				vm_read_flag4(char **arg, int x)
{
	g_vm->nambering[++g_vm->namber] = ft_atoi(arg[x]);
	if (g_vm->nambering[g_vm->namber] < 1 || g_vm->nambering[g_vm->namber] > 4)
	{
		g_vm->nambering[g_vm->namber] = 0;
		g_vm->error = 8;
	}
	return (0);
}
