/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_commands2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 18:59:28 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/20 09:31:21 by dmaznyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_com_fork(t_car *car)
{
	car->c_byte[0] = 2;
	vm_get_reg_dir(car, 0, 1);
	car->com_args[0] = ((short int)car->com_args[0]) % IDX_MOD;
	vm_init_car(car->car_pos, car->com_args[0], car->car_reg[0] * -1, car);
	car->car_next_pos = vm_find_next_pos(car);
	vm_car_clean(car);
}

void	vm_com_ifork(t_car *car)
{
	car->c_byte[0] = 2;
	vm_get_reg_dir(car, 0, 1);
	car->com_args[0] = ((short int)car->com_args[0]);
	vm_init_car(car->car_pos, car->com_args[0], car->car_reg[0] * -1, car);
	car->car_next_pos = vm_find_next_pos(car);
	vm_car_clean(car);
}

void	vm_com_st(t_car *car)
{
	int tmp;

	tmp = 0;
	if (car->c_byte[0] == 1 && (car->c_byte[1] == 1 || car->c_byte[1] == 3))
	{
		vm_get_reg_dir(car, 0, 2);
		if (car->c_byte[1] == 1)
			vm_get_reg_dir(car, 1, 3);
		else
			vm_get_ind(car, 1, 3);
		if (car->com_args[0] > 0 && car->com_args[0] < 17)
			tmp = car->car_reg[car->com_args[0]];
		if (car->c_byte[1] == 1 &&
				(car->com_args[0] > 0 && car->com_args[0] < 17) &&
				(car->com_args[1] > 0 && car->com_args[1] < 17))
			car->car_reg[car->com_args[1]] = tmp;
		else if (car->c_byte[1] == 3 && (car->com_args[0] > 0 &&
			car->com_args[0] < 17))
			vm_map_write(tmp, (car->car_pos +
						car->com_args[1] % IDX_MOD) % MEM_SIZE, car);
	}
	car->car_next_pos = vm_find_next_pos(car);
	vm_car_clean(car);
}

void	vm_com_sti(t_car *car)
{
	int i;

	i = 3;
	if (car->c_byte[0] == 1 && (car->c_byte[2] == 1 || car->c_byte[2] == 2))
	{
		vm_get_reg_dir(car, 0, 2);
		if (car->c_byte[1] == 1 || car->c_byte[1] == 2)
		{
			vm_get_reg_dir(car, 1, i);
			i += (car->c_byte[1] == 1) ? 1 : 2;
		}
		else
		{
			vm_get_ind(car, 1, i);
			i += 2;
		}
		vm_get_reg_dir(car, 2, i);
		vm_com_sti2(car, 0, 0, 0);
	}
	car->car_next_pos = vm_find_next_pos(car);
	vm_car_clean(car);
}

void	vm_com_sti2(t_car *car, int tmp, int tmp2, int tmp3)
{
	int cords;

	if (car->com_args[0] > 0 && car->com_args[0] < 17)
		tmp = car->car_reg[car->com_args[0]];
	if (car->c_byte[1] == 1 && (car->com_args[1] > 0 && car->com_args[1] < 17))
		tmp2 = car->car_reg[car->com_args[1]];
	else if (car->c_byte[1] == 2 || car->c_byte[1] == 3)
		tmp2 = car->com_args[1];
	if (car->c_byte[2] == 1 && (car->com_args[2] > 0 && car->com_args[2] < 17))
		tmp3 = car->car_reg[car->com_args[2]];
	else if (car->c_byte[2] == 2)
		tmp3 = car->com_args[2];
	cords = ((car->car_pos + (tmp2 + tmp3) % IDX_MOD) % MEM_SIZE);
	if ((car->com_args[0] > 0 && car->com_args[0] < 17) && ((car->c_byte[1] == 2
		|| car->c_byte[1] == 3) || (car->c_byte[1] == 1 &&
		(car->com_args[1] > 0 && car->com_args[1] < 17))) &&
		((car->c_byte[2] == 2) || (car->c_byte[2] == 1 &&
		(car->com_args[2] > 0 && car->com_args[2] < 17))))
		vm_map_write(tmp, cords, car);
}
