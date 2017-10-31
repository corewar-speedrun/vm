/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 13:22:03 by dverbyts          #+#    #+#             */
/*   Updated: 2017/10/31 13:22:06 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_read(t_vm *vm, int i, char **arg)
{
	int fd;
	int x;

	x = 0;
	while (++x < i)
	{
		if((fd = open(arg[x], O_RDONLY)) == -1 && vm->error == -1)
			vm->error = 2;
		if (arg[x][0] == '-' && vm->error == -1)
			vm_read_flag(vm, arg[x]);
		else if (vm_magic(vm, fd) == 1 && vm->error == -1)
			vm_parsing(vm, fd);
		else
			vm->error = 1;
		if (vm->error != -1)
			break ;
	}
}

void	vm_parsing(t_vm *vm, int fd)
{
	/*int l;

	l = 0;
	while (str[l])
	{

	}*/
}

void	vm_read_flag(t_vm *vm, char *str)
{
	return ;
}

int		vm_magic(t_vm *vm, int fd)
{
	union u_read	smpl;
	unsigned char	r[4];

	smpl.mg = COREWAR_EXEC_MAGIC;
	if (read(fd, &r, 4) != 4)
		vm->error = 2;
	if ((r[0] == smpl.bit[3] || r[0] == smpl.bit[0]) &&
		(r[1] == smpl.bit[2] || r[1] == smpl.bit[1]) &&
		(r[2] == smpl.bit[1] || r[2] == smpl.bit[2]) &&
		(r[3] == smpl.bit[0] || r[3] == smpl.bit[3]))
		return (1);
	else
		vm->error = 3;
	return (0);
}

/*
** int f - флаг какой ти данных проверяю.
**
** f = 1 - 4 байта - меджик число
** f = 2 - 132 байта - имя
** f = 3 - 4 байта - значение размера программы
** f = 4 - 2052 байта - коммент
** f = 5 - (значение из f3) байт - размер программы
*/
