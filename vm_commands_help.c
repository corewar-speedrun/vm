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

int		vm_find_next_pos(t_car *car, int args)
{

	return (2);
}

t_car		*vm_parse_code_byte(t_car *car)
{
	unsigned char	code_byte;

	code_byte = g_vm->map[0][car->car_pos + 1];
	car->c_byte[0] = (code_byte << 4) >> 6;
	car->c_byte[1] = (code_byte << 2) >> 6;
	car->c_byte[2] = code_byte >> 6;
	return (car);
}

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
	while (++z < 4)
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
	int				move;

	z = -1;
	while (++z < 2)
	{
		tmp1 = g_vm->map[0][car_pos + z + i];
		car->com_args[index] = (car->com_args[index] << 8) | tmp1;
	}
	tmp1 = g_vm->map[0][car->car_pos + i];
}