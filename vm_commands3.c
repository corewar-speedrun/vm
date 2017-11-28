/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_commands3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 17:22:52 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/20 09:33:02 by dmaznyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_com_aff(t_car *car)
{
	int		tmp;
	char	a;

	vm_get_reg_dir(car, 0, 2);
	if (car->c_byte[0] == 1 && car->com_args[0] > 0 && car->com_args[0] < 17 &&
			g_vm->flag_visualize == 0)
	{
		tmp = car->car_reg[car->com_args[0]];
		a = tmp % 256;
		write(1, "AFF: ", 5);
		write(1, &a, 1);
		write(1, "\n", 1);
	}
	car->car_next_pos = vm_find_next_pos(car);
	vm_car_clean(car);
}

void				vm_com_ldi(t_car *car)
{
	int i;

	i = 2;
	if ((car->c_byte[1] == 1 || car->c_byte[1] == 2) && car->c_byte[2] == 1)
	{
		if (car->c_byte[0] == 3)
			vm_get_ind(car, 0, i);
		else
			vm_get_reg_dir(car, 0, i);
		if (car->c_byte[0] == 1)
			i += 1;
		else
			i += 2;
		vm_get_reg_dir(car, 1, i);
		if (car->c_byte[1] == 1)
			i += 1;
		else
			i += 2;
		vm_get_reg_dir(car, 2, i);
		vm_com_ldi2(car);
	}
	car->car_next_pos = vm_find_next_pos(car);
	vm_car_clean(car);
}

void				vm_com_ldi2(t_car *car)
{
	int tmp;
	int tmp2;
	int tmp3;

	tmp3 = -1;
	tmp2 = 0;
	if (car->c_byte[0] == 1)
		car->com_args[0] = (short)car->car_reg[car->com_args[0]];
	if (car->c_byte[1] == 1)
		car->com_args[1] = (short)car->car_reg[car->com_args[1]];
	tmp = (car->car_pos + (car->com_args[0] + car->com_args[1]) % IDX_MOD);
	if (tmp < 0)
		tmp = (MEM_SIZE + tmp) % MEM_SIZE;
	while (++tmp3 < 4)
		tmp2 = (tmp2 << 8) | g_vm->map0[(tmp + tmp3) % MEM_SIZE];
	if (car->com_args[2] > 0 && car->com_args[2] < 17)
		car->car_reg[car->com_args[2]] = tmp2;
}

void				vm_com_lldi(t_car *car)
{
	int i;

	i = 2;
	if ((car->c_byte[1] == 1 || car->c_byte[1] == 2) && car->c_byte[2] == 1)
	{
		if (car->c_byte[0] == 3)
			vm_get_ind(car, 0, i);
		else
			vm_get_reg_dir(car, 0, i);
		if (car->c_byte[0] == 1)
			i += 1;
		else
			i += 2;
		vm_get_reg_dir(car, 1, i);
		if (car->c_byte[1] == 1)
			i += 1;
		else
			i += 2;
		vm_get_reg_dir(car, 2, i);
		vm_com_lldi2(car);
	}
	car->car_next_pos = vm_find_next_pos(car);
	vm_car_clean(car);
}

void				vm_com_lldi2(t_car *car)
{
	int tmp;
	int tmp2;
	int tmp3;

	tmp3 = -1;
	tmp2 = 0;
	if (car->c_byte[0] == 1)
		car->com_args[0] = car->car_reg[car->com_args[0]];
	if (car->c_byte[1] == 1)
		car->com_args[1] = car->car_reg[car->com_args[1]];
	tmp = car->com_args[0] + car->com_args[1] + car->car_pos;
	while (tmp < 0)
		tmp = (MEM_SIZE + tmp) % MEM_SIZE;
	while (++tmp3 < 4)
		tmp2 = (tmp2 << 8) | g_vm->map0[(tmp + tmp3) % MEM_SIZE];
	if (car->com_args[2] > 0 && car->com_args[2] < 17)
	{
		car->car_reg[car->com_args[2]] = tmp2;
		(car->car_reg[car->com_args[2]] == 0) ? (car->carry = TRUE) :
		(car->carry = FALSE);
	}
}
