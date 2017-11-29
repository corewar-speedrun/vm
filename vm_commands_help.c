/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_commands_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 16:24:08 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/20 09:49:11 by dmaznyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		vm_find_next_pos(t_car *car)
{
	int r;
	int c;

	c = car->comand;
	r = 2;
	if (c == 1 || c == 9 || c == 12 || c == 15)
		r -= 1;
	if (car->c_byte[0] == 1)
		r += 1;
	else if (car->c_byte[0] == 2 && ((c >= 1 && c < 9) || c == 13 || c == 16))
		r += 4;
	else if (car->c_byte[0] == 2 && ((c > 8 && c < 13) || c == 14 || c == 15))
		r += 2;
	else if (car->c_byte[0] == 3)
		r += 2;
	r = vm_find_next_pos2(car, r, c, 0);
	return (r);
}

int		vm_find_next_pos2(t_car *car, int r, int c, int i)
{
	if (c == 1 || c == 9 || c == 12 || c == 15 || c == 16)
		return (r);
	while (++i < 3)
	{
		if (car->c_byte[i] == 1)
			r += 1;
		else if (car->c_byte[i] == 2 && ((c > 1 && c < 9) || c == 13))
			r += 4;
		else if (car->c_byte[i] == 2 && (c == 10 || c == 11 || c == 14))
			r += 2;
		else if (car->c_byte[i] == 3)
			r += 2;
		if (c == 2 || c == 3 || c == 13)
			break ;
	}
	return (r);
}

void	vm_parse_code_byte(t_car *car)
{
	unsigned char code_byte;

	code_byte = g_vm->map0[(car->car_pos + 1) % MEM_SIZE];
	car->c_byte[0] = code_byte >> 6;
	car->c_byte[1] = (code_byte >> 4) & 3;
	car->c_byte[2] = (code_byte >> 2) & 3;
}

void	vm_get_reg_dir(t_car *car, int index, int i)
{
	unsigned char	tmp;
	int				z;
	int				size;
	int				c;

	c = car->comand;
	size = 0;
	if (car->c_byte[index] == 1)
		size = 1;
	else if (car->c_byte[index] == 2 && ((c >= 1 && c <= 8) ||
				c == 13 || c == 16))
		size = 4;
	else if (car->c_byte[index] == 2 && ((c >= 9 && c <= 12) ||
				c == 14 || c == 15))
		size = 2;
	z = -1;
	while (++z < size)
	{
		tmp = g_vm->map0[(car->car_pos + z + i) % MEM_SIZE];
		car->com_args[index] = (car->com_args[index] << 8) | tmp;
	}
	if (car->c_byte[index] == 2)
		car->com_args[index] = (short int)car->com_args[index];
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
	int				z;
	short int		ind;
	unsigned int	b;

	z = -1;
	ind = 0;
	while (++z < 2)
	{
		tmp = g_vm->map0[(car->car_pos + z + i) % MEM_SIZE];
		ind = (ind << 8) | tmp;
	}
	z = -1;
	(car->comand != 3) ? ind = ind % IDX_MOD : 0;
	if (car->comand == 3)
	{
		car->com_args[index] = ind;
		return ;
	}
	while (++z < 4)
	{
		b = (car->car_pos + ind + z);
		tmp = g_vm->map0[b % MEM_SIZE];
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
