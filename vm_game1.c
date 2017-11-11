/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_game1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 08:46:04 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/10 08:46:06 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_make_game(t_car *car)
{
	while (g_vm->game > 0)
	{

		car = g_vm->cars;
		while (car != NULL)
		{
			if (car->comand == 0)
				car = vm_read_comand(car);
			else if (car->count == 0 && car->comand != 0)
				car = vm_make_move(car);
			else
				car->count--;
			if (g_vm->map[2][car->car_pos] != 1)
				g_vm->map[2][car->car_pos] = 1;
			car = car->next_car;
		}
		if (++g_vm->cycle == g_vm->die_cycle)
			vm_car_to_die();
		vm_make_game2(NULL);
	}
}

void	vm_make_game2(t_car *car)
{
	car = g_vm->cars;
	while (car != NULL)
	{
		if (car->car_next_pos != 0)
			car = vm_car_next_pos(car);
		car = car->next_car;
	}
	// while (g_vm->game > 1)
	// {
	// 	/////////////////////////////////////////////////////////// для написания ифа под кейхук паузы и шага назад
	// }
}

/*
** vm_game/2 - главная ф-ция запуска игры.
** 
** размещает ботов на карте. потом будет передавать это все дальше.
** еще пилю это.////////////////////////////////////////////////////////////////////
*/

t_car		*vm_car_next_pos(t_car *car)
{
	if (car->car_next_pos < 1)
		return (car);
	if ((car->car_pos + car->car_next_pos) > MEM_SIZE)
		car->car_pos += car->car_next_pos;
	else
		car->car_pos = (car->car_pos + car->car_next_pos) - MEM_SIZE;
	car->car_next_pos = 0;
	return (car);
}

void	vm_car_to_die(void)
{
	t_car *tmp;
	t_car *start;

	start = g_vm->cars;
	while (start->live < 1 && start != NULL)
	{
		tmp = start->next_car;
		free(start);
		start = tmp;
	}
	g_vm->cars = start;
	if (g_vm->cars != NULL)
		vm_car_to_die2();
	g_vm->to_die -= CYCLE_DELTA;
	g_vm->die_cycle += g_vm->to_die;
}

void	vm_car_to_die2(void)
{
	t_car *tmp1;
	t_car *tmp2;
	t_car *tmp3;

	tmp1 = g_vm->cars;
	tmp2 = tmp1->next_car;
	while (tmp2 != NULL)
	{
		tmp3 = tmp2->next_car;
		if (tmp2->live < 1)
		{
			free(tmp2);
			tmp1->next_car = tmp3;
		}
		else
			tmp1 = tmp1->next_car;
		tmp2 = tmp1->next_car;
	}
	tmp1 = g_vm->cars;
	while (tmp1 != NULL)
	{
		tmp1->live = 0;
		tmp1 = tmp1->next_car;
	}
}
