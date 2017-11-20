/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_game1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 08:46:04 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/20 09:46:35 by dmaznyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_make_game(t_car *car)
{
	while (g_vm->game > 0)
	{
		car = g_vm->cars;
		if (g_vm->flag_visualize == 1)
			g_vm->sleep = ncurses(g_vm->sleep);
		while (car != NULL)
		{
			if (g_vm->map2[car->car_pos] != 1)
				g_vm->map2[car->car_pos] = 1;
			if (car->comand == 0)
				vm_read_comand(car);
			else if (car->count == 0 && car->comand != 0)
				vm_make_move(car);
			if (car->count > 0)
				car->count--;
			car = car->next_car;
		}
		vm_make_game2(car, -1);
		if (g_vm->damp == g_vm->cycle && g_vm->flag_visualize != 1)
		{
			print_maps();
			break ;
		}
	}
}

void	vm_make_game2(t_car *car, int i)
{
	if (++g_vm->cycle == g_vm->die_cycle)
		vm_car_to_die(NULL, NULL);
	car = g_vm->cars;
	while (car != NULL)
	{
		if (car->car_next_pos != 0)
			vm_car_next_pos(car);
		car = car->next_car;
	}
	while (++i < MEM_SIZE)
	{
		if (g_vm->map3[i] > 0)
		{
			if (g_vm->map3[i] >= 100)
				g_vm->map3[i] = 0;
			else
				g_vm->map3[i]++;
		}
	}
}

/*
** vm_game/2 - главная ф-ция запуска игры.
** размещает ботов на карте. потом будет передавать это все дальше.
*/

void	vm_car_next_pos(t_car *car)
{
	if (car->car_next_pos < 0)
		car->car_next_pos = (MEM_SIZE + car->car_next_pos) % MEM_SIZE;
	if (g_vm->map2[car->car_pos] == 1)
		g_vm->map2[car->car_pos] = 0;
	car->car_pos = ((car->car_pos + car->car_next_pos) % MEM_SIZE);
	if (g_vm->map2[car->car_pos] != 1)
		g_vm->map2[car->car_pos] = 1;
	car->car_next_pos = 0;
}

void	vm_car_to_die(t_car *tmp, t_car *start)
{
	start = g_vm->cars;
	while (start != NULL && start->live < 1)
	{
		tmp = start->next_car;
		if (g_vm->map2[start->car_pos] == 1)
			g_vm->map2[start->car_pos] = 0;
		free(start);
		g_vm->cars_nmbr -= 1;
		start = tmp;
	}
	g_vm->cars = start;
	if (g_vm->live_checks >= NBR_LIVE || g_vm->max_live_checks <= 0)
	{
		g_vm->to_die -= CYCLE_DELTA;
		g_vm->die_cycle += g_vm->to_die;
		g_vm->live_checks = 0;
		g_vm->max_live_checks = MAX_CHECKS;
	}
	else
		g_vm->max_live_checks--;
	if (g_vm->cars != NULL && g_vm->to_die > 0)
		vm_car_to_die2(NULL, NULL, NULL);
	else
		vm_finish_game();
}

void	vm_car_to_die2(t_car *tmp1, t_car *tmp2, t_car *tmp3)
{
	tmp1 = g_vm->cars;
	tmp2 = tmp1->next_car;
	while (tmp2 != NULL)
	{
		tmp3 = tmp2->next_car;
		if (tmp2->live < 1)
		{
			if (g_vm->map2[tmp2->car_pos] == 1)
				g_vm->map2[tmp2->car_pos] = 0;
			free(tmp2);
			g_vm->cars_nmbr -= 1;
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
