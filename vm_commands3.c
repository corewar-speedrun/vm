/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_commands3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 15:07:20 by nsharova          #+#    #+#             */
/*   Updated: 2017/11/13 15:07:24 by nsharova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_car		*vm_com_and(t_car *car)
{
	int				i;
	unsigned char	tmp;

	i = 2;
	i += vm_get_first_arg(car, i);
	i += vm_get_second_arg(car, i);
	if (vm_get_first_arg  && vm_get_second_arg && car->c_byte[0] == 1)
	{
		tmp = g_vm->map[0][car->car_pos + i];
		if (tmp >= 0 && tmp < 16)
		{
			car->car_reg[tmp] = car->com_args[0] & car->com_args[1];
			(car->car_reg[tmp] == 0) ? (car->carry = 1) : 0;
			car->car_next_pos = i;
		}	
	}
	else 
		car->car_next_pos = vm_find_next_pos(car, 3);
	car->count = 0;
	car->comand = 0;
	return (car);
}

t_car		*vm_com_or(t_car *car)
{
	int				i;
	unsigned char	tmp;

	i = 2;
	i += vm_get_first_arg(car, i);
	i += vm_get_second_arg(car, i);
	if (vm_get_first_arg  && vm_get_second_arg && car->c_byte[0] == 1)
	{
		tmp = g_vm->map[0][car->car_pos + i];
		if (tmp >= 0 && tmp < 16)
		{
			car->car_reg[tmp] = car->com_args[0] | car->com_args[1];
			(car->car_reg[tmp] == 0) ? (car->carry = 1) : 0;
			car->car_next_pos = i;
		}	
	}
	else 
		car->car_next_pos = vm_find_next_pos(car, 3);
	car->count = 0;
	car->comand = 0;
	return (car);
}

t_car		*vm_com_xor(t_car *car)
{
	int				i;
	unsigned char	tmp;

	i = 2;
	i += vm_get_first_arg(car, i);
	i += vm_get_second_arg(car, i);
	if (vm_get_first_arg  && vm_get_second_arg && car->c_byte[0] == 1)
	{
		tmp = g_vm->map[0][car->car_pos + i];
		if (tmp >= 0 && tmp < 16)
		{
			car->car_reg[tmp] = car->com_args[0] ^ car->com_args[1];
			(car->car_reg[tmp] == 0) ? (car->carry = 1) : 0;
			car->car_next_pos = i;
		}	
	}
	else 
		car->car_next_pos = vm_find_next_pos(car, 3);
	car->count = 0;
	car->comand = 0;
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

// int		vm_get_first_arg(t_car *car, int i)
// {
// 	if (car->c_byte[0] == REG_CODE)
// 		return (vm_get_t_reg(car, 0, i));
// 	else if (car->c_byte[0] == DIR_CODE)
// 		return (vm_get_t_dir(car, 0, i));
// 	else if (car->c_byte[0] == IND_CODE)
// 		return (vm_get_t_ind(car, 0, i));
// 	return (0);
// }
/// REG_CODE == 1
/// DIR_CODE == 2
/// IND_CODE == 3
/// можно просто заменить дефайны на значения

/// обе ф-ции делают идентичную задачу, меняется одна цифра. чтобы не плодить ф-ции, я бы урезал эти две ф-ции в одну. 
/// vm_get_arg(t_car *car, int arg, int i)
/// arg  == номер аргумента, который хотим взять

// int		vm_get_second_arg(t_car *car, int i)
// {
// 	if (car->c_byte[1] == REG_CODE)
// 		return (vm_get_t_reg(car, 1, i));
// 	else if (car->c_byte[1] == DIR_CODE)
// 		return (vm_get_t_dir(car, 1, i));
// 	else if (car->c_byte[1] == IND_CODE)
// 		return (vm_get_t_ind(car, 1, i));
// 	return (0);
// }

