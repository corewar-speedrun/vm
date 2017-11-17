/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_commands_help2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 15:07:20 by nsharova          #+#    #+#             */
/*   Updated: 2017/11/13 15:07:24 by nsharova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		vm_get_arg(t_car *car, int arg, int i)
{
	if (car->c_byte[arg] == 1)
		return (vm_get_t_reg(car, arg, i));
	else if (car->c_byte[arg] == 2)
		return (vm_get_t_dir(car, arg, i));
	else if (car->c_byte[arg] == 3)
		return (vm_get_t_ind(car, arg, i));
	return (0);
}

int		vm_get_t_reg(t_car *car, int index, int i)
{
	unsigned char	tmp1;

	tmp1 = g_vm->map0[(car->car_pos + i) % MEM_SIZE];
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
	int				size;

	z = -1;
	size = ((car->comand >= 1 && car->comand <= 8) ||
		car->comand == 13 || car->comand == 16) ? 4 : 2;
	while (++z < size)
	{
		tmp1 = g_vm->map0[(car->car_pos + z + i) % MEM_SIZE];
		car->com_args[index] = (car->com_args[index] << 8) | tmp1;
	}
	return (size);
}

int		vm_get_t_ind(t_car *car, int index, int i)
{
	unsigned char	tmp1;
	unsigned char	tmp2;
	int 			z;
	short int		ind;

	z = -1;
	ind = 0;
	while (++z < 2)
	{
		tmp1 = g_vm->map0[car->car_pos + z + i];
		ind = (ind << 8) | tmp1;
	}
	z = -1;
	ind = (car->comand == 13) ? ind : ind % IDX_MOD;
	while (++z < 4)
	{
		tmp2 = g_vm->map0[(car->car_pos + ind + z) % MEM_SIZE];
		car->com_args[index] = (car->com_args[index] << 8) | tmp2;
	}
	return (2);
}