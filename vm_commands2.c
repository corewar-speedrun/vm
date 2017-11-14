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
	unsigned char	tmp;
	int 			z;

	car->car_next_pos = 3;
	if (car->carry == FALSE)
		return ;
	z = 0;
	while (++z < 3)
	{
		tmp = g_vm->map[0][car->car_pos + z];
		car->com_args[0] = (car->com_args[0] << 8) | tmp;
	}
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
	unsigned char	tmp;
	int 			z;
	t_car			*new;

	z = 0;
	while (++z < 3)
	{
		tmp = g_vm->map[0][car->car_pos + z];
		car->com_args[0] = (car->com_args[0] << 8) | tmp;
	}
	vm_init_car(car->car_pos, car->com_args[0], car->car_reg[1], car);
	car->car_next_pos = car->car_pos + 3;
	vm_car_clean(car);
}
