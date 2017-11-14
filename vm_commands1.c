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

t_car	*vm_com_live(t_car *car)
{
	unsigned char	tmp;
	int 			champ_namber;
	int 			z;

	z = 0;
	champ_namber = 0;
	while (++z < 4)
	{
		tmp = g_vm->map[0][car->car_pos + z];
		champ_namber = (champ_namber << 8) | tmp;
	}
	if (champ_namber > 0 && champ_namber <= g_vm->champs_nmbr)
	{
		g_vm->champs[champ_namber]->live += 1;
		g_vm->champs[champ_namber]->last_live = g_vm->cycle;
		if (g_vm->flag_say_alive == 1 && g_vm->flag_visualize != 1)
			vm_com_live2(champ_namber);
	}
	car->car_next_pos = 5;
	car->live += 1;
	vm_car_clean(car);
	return (car);
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

t_car		*vm_com_add(t_car *car)
{
	unsigned char	tmp1;
	unsigned char	tmp2;
	unsigned char	tmp3;

	car->carry = 0;
	vm_parse_code_byte(car);
	if (car->c_byte[0] == 1 && car->c_byte[1] == 1 && car->c_byte[2] == 1)
	{
		tmp1 = g_vm->map[0][car->car_pos + 2];
		tmp2 = g_vm->map[0][car->car_pos + 3];
		tmp3 = g_vm->map[0][car->car_pos + 4];
		if ((tmp1 >= 0 && tmp1 < 16) && (tmp2 >= 0 && tmp2 < 16) && 
			(tmp3 >= 0 && tmp3 < 16))
		{
			car->car_reg[tmp3] = car->car_reg[tmp1] + car->car_reg[tmp2];
			car->carry = 1;
			car->car_next_pos = 5;
		}
	}
	else 
		car->car_next_pos = vm_find_next_pos(car, 4);
	vm_car_clean(car);
	return (car);
}



t_car		*vm_com_sub(t_car *car)
{
	unsigned char	tmp1;
	unsigned char	tmp2;
	unsigned char	tmp3;

	car->carry = 0;
	vm_parse_code_byte(car);
	if (car->c_byte[0] == 1 && car->c_byte[1] == 1 && car->c_byte[2] == 1)
	{
		tmp1 = g_vm->map[0][car->car_pos + 2];
		tmp2 = g_vm->map[0][car->car_pos + 3];
		tmp3 = g_vm->map[0][car->car_pos + 4];
		if ((tmp1 >= 0 && tmp1 < 16) && (tmp2 >= 0 && tmp2 < 16) && 
			(tmp3 >= 0 && tmp3 < 16))
		{
			car->car_reg[tmp3] = car->car_reg[tmp1] - car->car_reg[tmp2];
			car->carry = 1;
			car->car_next_pos = 5;
		}
	}
	else 
		car->car_next_pos = vm_find_next_pos(car, 5);
	vm_car_clean(car);
	return (car);
}
