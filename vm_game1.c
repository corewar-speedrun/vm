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

void	vm_make_game(t_car *move)
{
	while (g_vm->game > 0)
	{

		move = g_vm->cars;
		while (move != NULL)
		{
			if (move->comand == 0)
				move = vm_read_comand(move);
			else if (move->count == 0 && move->comand != 0)
				move = vm_make_move(move);
			else
				move->count--;
			if (g_vm->map[2][move->car_pos] != 1)
				g_vm->map[2][move->car_pos] = 1;
			move = move->next_car;
		}
		if (++g_vm->cycle == g_vm->die_cycle)
			vm_car_to_die();
		vm_make_game2(NULL);
	}
}

void	vm_make_game2(t_car *move)
{
	move = g_vm->cars;
	while (move != NULL)
	{
		if (move->car_next_pos != 0)
			move = vm_car_next_pos(move);
		move = move->next_car;
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

t_car		*vm_car_next_pos(t_car *move)
{
	if (move->car_next_pos < 1)
		return (move);

	if ((move->car_pos + move->car_next_pos) > MEM_SIZE)
		move->car_pos += move->car_next_pos;
	else
		move->car_pos = (move->car_pos + move->car_next_pos) - MEM_SIZE;
	move->car_next_pos = 0;
	return (move);
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
