/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_commands4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsharova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 15:07:20 by nsharova          #+#    #+#             */
/*   Updated: 2017/11/13 15:07:24 by nsharova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		vm_com_and(t_car *car)
{
	int				i;
	unsigned char	tmp;

	i = 2;
	i += vm_get_arg(car, 0, i);
	i += vm_get_arg(car, 1, i);
	if (vm_get_arg(car, 0, i) && vm_get_arg(car, 1, i) && car->c_byte[2] == 1)
	{
		tmp = g_vm->map[0][(car->car_pos + i) % MEM_SIZE];
		if (tmp >= 0 && tmp < 16)
		{
			car->car_reg[tmp] = car->com_args[0] & car->com_args[1];
			(car->car_reg[tmp] == 0) ? (car->carry = 1) : 0;
			car->car_next_pos = i;
		}	
	}
	else 
	{
		car->car_next_pos = vm_find_next_pos(car);
		car->carry = 0;
	}
	vm_car_clean(car);
}

void		vm_com_or(t_car *car)
{
	int				i;
	unsigned char	tmp;

	i = 2;
	i += vm_get_arg(car, 0, i);
	i += vm_get_arg(car, 1, i);
	if (vm_get_arg(car, 0, i) && vm_get_arg(car, 1, i) && car->c_byte[2] == 1)
	{
		tmp = g_vm->map[0][(car->car_pos + i) % MEM_SIZE];
		if (tmp >= 0 && tmp < 16)
		{
			car->car_reg[tmp] = car->com_args[0] | car->com_args[1];
			(car->car_reg[tmp] == 0) ? (car->carry = 1) : 0;
			car->car_next_pos = i;
		}	
	}
	else 
	{
		car->car_next_pos = vm_find_next_pos(car);
		car->carry = 0;
	}
	vm_car_clean(car);
}

void		vm_com_xor(t_car *car)
{
	int				i;
	unsigned char	tmp;

	i = 2;
	i += vm_get_arg(car, 0, i);
	i += vm_get_arg(car, 1, i);
	if (vm_get_arg(car, 0, i) && vm_get_arg(car, 1, i) && car->c_byte[2] == 1)
	{
		tmp = g_vm->map[0][(car->car_pos + i) % MEM_SIZE];
		if (tmp >= 0 && tmp < 16)
		{
			car->car_reg[tmp] = car->com_args[0] ^ car->com_args[1];
			(car->car_reg[tmp] == 0) ? (car->carry = 1) : 0;
			car->car_next_pos = i;
		}	
	}
	else 
	{
		car->car_next_pos = vm_find_next_pos(car);
		car->carry = 0;
	}
	vm_car_clean(car);
}

void		vm_com_ld(t_car *car)
{
	int				i;
	unsigned char	tmp;

	i = 2;
	i += vm_get_arg(car, 0, i);
	if (vm_get_arg(car, 0, i) && car->c_byte[1] == 1)
	{
		tmp = g_vm->map[0][(car->car_pos + i) % MEM_SIZE];
		if (tmp >= 0 && tmp < 16)
		{
			car->car_reg[tmp] = car->com_args[0];
			(car->car_reg[tmp] == 0) ? (car->carry = 1) : 0;
			car->car_next_pos = i;
		}	
	}
	else 
	{
		car->car_next_pos = vm_find_next_pos(car);
		car->carry = 0;
	}
	vm_car_clean(car);
}


void		vm_com_lld(t_car *car)
{
	int				i;
	unsigned char	tmp;

	i = 2;
	i += vm_get_arg(car, 0, i);
	if (vm_get_arg(car, 0, i) && car->c_byte[1] == 1)
	{
		tmp = g_vm->map[0][(car->car_pos + i) % MEM_SIZE];
		if (tmp >= 0 && tmp < 16)
		{
			car->car_reg[tmp] = car->com_args[0];
			(car->car_reg[tmp] == 0) ? (car->carry = 1) : 0;
			car->car_next_pos = i;
		}	
	}
	else 
	{
		car->car_next_pos = vm_find_next_pos(car);
		car->carry = 0;
	}
	vm_car_clean(car);
}
