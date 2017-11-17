/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_commands1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 15:07:20 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/13 15:07:24 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_com_live(t_car *car)/////////////////////
{
	int 			champ_namber;

	car->c_byte[0] = 2;
	vm_get_reg_dir(car, 0, 1);
	champ_namber = car->com_args[0] * -1;
	if (champ_namber > 0 && champ_namber <= g_vm->champs_nmbr)
	{
		g_vm->champs[champ_namber]->live += 1;
		g_vm->champs[champ_namber]->last_live = g_vm->cycle;
		if (g_vm->flag_say_alive == 1 && g_vm->flag_visualize != 1)
			vm_com_live2(champ_namber);
	}
	car->car_next_pos = vm_find_next_pos(car);
	car->live += 1;
	vm_car_clean(car);
}

void	vm_com_live2(int champ_namber)
{
	ft_putstr("Player \0");
	ft_putnbr(champ_namber);
	write(1, " (", 2);
	ft_putstr(g_vm->champs[champ_namber]->name);
	write(1, ") ", 2);
	ft_putstr("is said to be alive\n\0");	
}

void		vm_com_add(t_car *car)
{
	unsigned char	tmp1;
	unsigned char	tmp2;
	unsigned char	tmp3;

	car->carry = FALSE;
	if (car->c_byte[0] == 1 && car->c_byte[1] == 1 && car->c_byte[2] == 1)
	{
		tmp1 = g_vm->map[0][(car->car_pos + 2) % MEM_SIZE];
		tmp2 = g_vm->map[0][(car->car_pos + 3) % MEM_SIZE];
		tmp3 = g_vm->map[0][(car->car_pos + 4) % MEM_SIZE];
		if ((tmp1 >= 0 && tmp1 < 16) && (tmp2 >= 0 && tmp2 < 16) && 
			(tmp3 >= 0 && tmp3 < 16))
		{
			car->car_reg[tmp3] = car->car_reg[tmp1] + car->car_reg[tmp2];
			car->carry = TRUE;
		}
	}
	car->car_next_pos = vm_find_next_pos(car);
	vm_car_clean(car);
}

void		vm_com_sub(t_car *car)
{
	unsigned char	tmp1;
	unsigned char	tmp2;
	unsigned char	tmp3;

	car->carry = FALSE;
	if (car->c_byte[0] == 1 && car->c_byte[1] == 1 && car->c_byte[2] == 1)
	{
		tmp1 = g_vm->map[0][(car->car_pos + 2) % MEM_SIZE];
		tmp2 = g_vm->map[0][(car->car_pos + 3) % MEM_SIZE];
		tmp3 = g_vm->map[0][(car->car_pos + 4) % MEM_SIZE];
		if ((tmp1 >= 0 && tmp1 < 16) && (tmp2 >= 0 && tmp2 < 16) && 
			(tmp3 >= 0 && tmp3 < 16))
		{
			car->car_reg[tmp3] = car->car_reg[tmp1] - car->car_reg[tmp2];
			car->carry = TRUE;
		}
	}
	car->car_next_pos = vm_find_next_pos(car);
	vm_car_clean(car);
}

void	vm_com_zjmp(t_car *car)
{
	car->car_next_pos = 3;
	if (car->carry == FALSE)
		return ;
	car->c_byte[0] = 2;
	vm_get_reg_dir(car, 0, 1);
	car->car_next_pos = (short int)car->com_args[0];
	vm_car_clean(car);
}
