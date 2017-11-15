/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_commands_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 16:24:08 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/13 16:24:11 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		vm_find_next_pos(t_car *car)
{
	int i;
	int r;
	int c_nmbr;

	c_nmbr = car->comand;
	i = -1;
	r = 2;
	while (++i < 3)
	{
		if (car->c_byte[i] == 1)
			r += 1;
		else if (car->c_byte[i] == 2 && ((c_nmbr >= 1 && c_nmbr <= 8) ||
			c_nmbr == 13 || c_nmbr == 16))
			r += 4;
		else if (car->c_byte[i] == 2 && ((c_nmbr >= 9 && c_nmbr <= 12) ||
			c_nmbr == 14 || c_nmbr == 15))
			r += 2;
		else if (car->c_byte[i] == 3)
			r += 2;
	}
	return (r);
}

void	vm_car_clean(t_car *car)
{
	int i;

	i = -1;
	while (++i < 3)
	{
		car->c_byte[i] = 0;
		car->com_args[i] = 0;
	}
	car->count = 0;
	car->comand = 0;
}

void		vm_parse_code_byte(t_car *car)
{
	unsigned char	code_byte;

	code_byte = g_vm->map[0][car->car_pos + 1];
	car->c_byte[0] = (code_byte << 4) >> 6;
	car->c_byte[1] = (code_byte << 2) >> 6;
	car->c_byte[2] = code_byte >> 6;
}

void	vm_get_reg_dir(t_car *car, int index, int i)
{
	unsigned char	tmp;
	int				z;
	int				size;
	int				c_nmbr;

	c_nmbr = car->comand;
	size = 0;
	if (car->c_byte[i] == 1)
		size = 1;
	else if (car->c_byte[i] == 2 && ((c_nmbr >= 1 && c_nmbr <= 8) ||
		c_nmbr == 13 || c_nmbr == 16))
		size = 4;
	else if (car->c_byte[i] == 2 && ((c_nmbr >= 9 && c_nmbr <= 12) ||
		c_nmbr == 14 || c_nmbr == 15))
		size = 2;
	else if (car->c_byte[i] == 3)
		size = 2;
	z = -1;
	while (++z < size)
	{
		tmp = g_vm->map[0][(car->car_pos + z + i) % MEM_SIZE];
		car->com_args[index] = (car->com_args[index] << 8) | tmp;
	}
}

/*
** vm_get_reg_dir - считывает и записывает в com_args[index] t_reg и t_dir
**
** index - номер аргумента, с которым работаем (от 0 до 2)
** i - индекс смещения по памяти от car_pos
*/

void	vm_get_ind(t_car *car, int index, int i)
{
	unsigned char	tmp;
	int 			z;
	short int		ind;

	z = -1;
	ind = 0;
	while (++z < 2)
	{
		tmp = g_vm->map[0][car->car_pos + z + i];
		ind = (ind << 8) | tmp;
	}
	z = -1;
	if (car->comand == 2 || car->comand == 10)
		ind = ind % IDX_MOD;
	tmp = 0;
	while (++z < 4)
	{
		tmp = g_vm->map[0][(car->car_pos + ind + z) % MEM_SIZE];
		car->com_args[index] = (car->com_args[index] << 8) | tmp;
	}
}

/*
** vm_get_ind - считывает адрес. парсит его. по адресу считывает чему равен
** и записывает в com_args[index] t_ind
**
** index - номер аргумента, с которым работаем (от 0 до 2)
** i - индекс смещения по памяти от car_pos
*/
