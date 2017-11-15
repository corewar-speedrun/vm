/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_commands2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 18:59:28 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/14 18:59:30 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_com_zjmp(t_car *car)
{
	car->car_next_pos = 3;
	if (car->carry == FALSE)
		return ;
	car->c_byte[0] = 2;
	vm_get_reg_dir(car, 0, 1);
	car->car_next_pos = car->car_pos + car->com_args[0];
	vm_car_clean(car);
}

void	vm_com_fork(t_car *car)
{
	unsigned char	tmp;
	int 			z;
	t_car			*new;

	z = 0;
	while (++z < 3)
	{
		tmp = g_vm->map[0][car->car_pos + z];
		car->com_args[0] = (car->com_args[0] << 8) | tmp;
	}
	car->com_args[0] = car->com_args[0] % IDX_MOD;
	vm_init_car(car->car_pos, car->com_args[0], car->car_reg[1], car);
	car->car_next_pos = car->car_pos + 3;
	vm_car_clean(car);
}

void	vm_com_ifork(t_car *car)
{
	car->c_byte[0] = 2;
	vm_get_reg_dir(car, 0, 1);
	vm_init_car(car->car_pos, car->com_args[0], car->car_reg[1], car);
	car->car_next_pos = car->car_pos + 3;
	vm_car_clean(car);
}

void	vm_com_st(t_car *car)
{
	if (car->c_byte[0] == 1 && (car->c_byte[1] == 1 || car->c_byte[1] == 3))
	{
		car->com_args[0] = g_vm->map[0][car->car_pos + 2];
		if (car->c_byte[1] == 1)
			car->com_args[1] = g_vm->map[0][car->car_pos + 3];
		else
		{
			car->com_args[1] = (car->com_args[1] << 8) | g_vm->map[0][car->car_pos + 3];
			car->com_args[1] = (car->com_args[1] << 8) | g_vm->map[0][car->car_pos + 4];
		}
		if (car->c_byte[1] == 1 &&
			(car->com_args[0] > 0 && car->com_args[0] < 17) && 
			(car->com_args[1] > 0 && car->com_args[1] < 17))
			car->car_reg[car->com_args[1]] = car->car_reg[car->com_args[0]];
		else if (car->c_byte[1] == 3 &&
			(car->com_args[0] > 0 && car->com_args[0] < 17))
			g_vm->map[0][(car->car_pos + (car->car_reg[1] % IDX_MOD)) % MEM_SIZE] = car->car_reg[car->com_args[0]];
	}
	car->car_next_pos = vm_find_next_pos(car);
	vm_car_clean(car);
}

значение а1 записывается по индексу ((а2 + а3) % IDX_MOD) . Если а2 T_IND - берет 4-байтовое значение по адресу а2, 
складывает его с а3, и только потом берет % IDX_MOD, T_IND адресс может быть в диапазоне [-32768, 32767].

Take a registry, and two indexes (potentially registries) add the
two indexes, and use this result as an address where the value of the first parameter
will be copied.

sti r2,%4,%5 sti copies REG_SIZE bytes of r2 at address (4 + 5)
Parameters 2 and 3 are indexes. If they are, in fact, registers,
we’ll use their contents as indexes.

T_REG	T_REG | T_DIR | T_IND	T_DIR | T_REG						

void	vm_com_sti(t_car *car)
{
	if (car->c_byte[0] == 1 && (car->c_byte[1] == 1 || car->c_byte[1] == 3))
	{
		car->com_args[0] = g_vm->map[0][car->car_pos + 2];
		if (car->c_byte[1] == 1)
			car->com_args[1] = g_vm->map[0][car->car_pos + 3];
		else
		{
			car->com_args[1] = (car->com_args[1] << 8) | g_vm->map[0][car->car_pos + 3];
			car->com_args[1] = (car->com_args[1] << 8) | g_vm->map[0][car->car_pos + 4];
		}
		if (car->c_byte[1] == 1 &&
			(car->com_args[0] > 0 && car->com_args[0] < 17) && 
			(car->com_args[1] > 0 && car->com_args[1] < 17))
			car->car_reg[car->com_args[1]] = car->car_reg[car->com_args[0]];
		else if (car->c_byte[1] == 3 &&
			(car->com_args[0] > 0 && car->com_args[0] < 17))
			g_vm->map[0][(car->car_pos + (car->car_reg[1] % IDX_MOD)) % MEM_SIZE] = car->car_reg[car->com_args[0]];
	}
	car->car_next_pos = vm_find_next_pos(car);
	vm_car_clean(car);
}






















