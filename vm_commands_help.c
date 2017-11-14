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

int		vm_find_next_pos(t_car *car, int c_nmbr)
{
	int i;
	int r;

	i = -1;
	r = 2;
	while (++i < 3)
	{
		if (car->c_byte[i] == 1)
			r += 1;
		else if (car->c_byte[i] == 2 && ((c_nmbr >= 1 && c_nmbr <= 8) ||
			c_nmbr == 13 || c_nmbr == 16))
			r += 2;
		else if (car->c_byte[i] == 2 && ((c_nmbr >= 9 && c_nmbr <= 12) ||
			c_nmbr == 14 || c_nmbr == 15))
			r += 4;
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

/////////////// заче возвращать ничего не значащие инты? возвращай сразу нужные значения.

int		vm_get_t_reg(t_car *car, int index, int i)
{
	unsigned char	tmp1;

	tmp1 = g_vm->map[0][car_pos + i];
	if (tmp1 >= 0 && tmp1 < 16)
	{
		car->com_args[index] = car->car_reg[tmp1];
		return (1);
	}
	return (0); 
}

int		vm_get_t_dir(t_car *car, int index, int i)
{
	unsigned char	tmp1;
	int 			z;

	z = -1;
	while (++z < 4) ////////////////////////////////////// иногда t_dir возвращает 2 байта, иногда 4.
	{
		tmp1 = g_vm->map[0][car_pos + z + i];
		car->com_args[index] = (car->com_args[index] << 8) | tmp1;
	}
	return (4);
}

int		vm_get_t_ind(t_car *car, int index, int i)
{
	unsigned char	tmp1;
	int 			z;
	int				move; //////////////////////////////////// не используется

	z = -1;
	while (++z < 2)
	{
		tmp1 = g_vm->map[0][car_pos + z + i];
		car->com_args[index] = (car->com_args[index] << 8) | tmp1;
	}
	tmp1 = g_vm->map[0][car->car_pos + i];
}

// int		vm_get_arg(t_car *car, int arg, int i)
// {
// 	if (car->c_byte[0] == REG_CODE)
// 		return (vm_get_t_reg(car, arg, i));
// 	else if (car->c_byte[0] == DIR_CODE)
// 		return (vm_get_t_dir(car, arg, i));
// 	else if (car->c_byte[0] == IND_CODE)
// 		return (vm_get_t_ind(car, arg, i));
// 	return (0);
// }