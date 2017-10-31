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
	if (vm->error == -1)
		tmp->name = (char *)vm_read_script(PROG_NAME_LENGTH + 4, fd, 1);
	if (vm->error == -1)
		tmp->size = ft_atoi_base(vm_read_script(4, fd, 0), 16);
	if (vm->error == -1)
		tmp->comment = (char *)vm_read_script(COMMENT_LENGTH + 4, fd, 1);
	if (vm->error == -1 && tmp->size <= (MEM_SIZE / 6))
		tmp->src = (tmp->size, fd);
	else if (vm->error == -1)
		vm->error = 4;


	return (tmp);
}

unsigned char *vm_read_script(int i, int fd, int flag)
{
	unsigned char	buf[i];

	if (read(fd, &buf, i) != i)
	{
		vm->error = 2;
		return (0);
	}
	if (flag != 0 && (buf[i] != 0 || buf[i - 1] != 0 || buf[i - 2] != 0 || 
		buf[i - 3] != 0))
	{
		vm->error = 5;
		return (0);
	}


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
	if (vm->error == -1 && (r[0] == smpl.bit[3] || r[0] == smpl.bit[0]) &&
		(r[1] == smpl.bit[2] || r[1] == smpl.bit[1]) &&
		(r[2] == smpl.bit[1] || r[2] == smpl.bit[2]) &&
		(r[3] == smpl.bit[0] || r[3] == smpl.bit[3]))
		return (1);
	else if (vm->error == -1)
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

int	test_base(char nb)
{
	if (nb >= '0' && nb <= '9')
		return (nb - '0');
	else if (nb >= 'a' && nb <= 'z')
		return (nb - 'a' + 10);
	else if (nb >= 'A' && nb <= 'Z')
		return (nb - 'A' + 10);
	else
		return (-1);
}

int ft_atoi_base(const char *str, int str_base)
{
	int temp;
	int value;
	int sign;
	
	value = 0;
	sign = 1;
	if(str_base < 2 || str_base > 16 || (!str))
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\f' ||
		   *str == '\v' || *str == '\n' || *str == '\r')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	temp = test_base(*str);
	while (temp >= 0 && temp <= str_base)
	{
		value = value * str_base + temp;
		str++;
		temp = test_base(*str);
	}
	return(value * sign);
}