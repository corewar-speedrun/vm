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
			vm->champs[++vm->champs_nmbr] = vm_parsing(vm, fd);
		else
			vm->error = 1;
		if (vm->error != -1)
			break ;
	}
}

t_champ	*vm_parsing(t_vm *vm, int fd)
{
	t_champ	*tmp;

	if (!(tmp = (t_champ *)malloc(sizeof(t_champ) * 1)))
		return (NULL);
	ft_bzero(tmp, sizeof(t_champ));
	tmp->name = (char *)vm_read_script(PROG_NAME_LENGTH + 4, fd);
	tmp->size = ft_atoi_base(vm_read_script(4, fd), 16);
	tmp->comment = (char *)vm_read_script(COMMENT_LENGTH + 4, fd);
	if (tmp->size <= (MEM_SIZE / 6))
		tmp->src = (tmp->size, fd);
	else
		vm->error = 4;


	return (tmp);
}

unsigned char *vm_read_script(int i, int fd)
{

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


///////////////////
//make atoi_base(unsigned char *src, int base);
//////////////////