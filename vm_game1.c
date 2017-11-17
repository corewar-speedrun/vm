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
    t_vm *tmp = g_vm;

	g_vm->sleep = 10000;
	while (g_vm->game > 0)
	{
		car = g_vm->cars;
<<<<<<< HEAD
//		if (g_vm->flag_visualize == 1)
//         g_vm->sleep = ncurses(g_vm->sleep);
=======
		 if (g_vm->flag_visualize == 1)
		 	g_vm->sleep = ncurses(g_vm->sleep);
>>>>>>> 28b809d860176eb4a250363e4c935ea050e5e355
		while (car != NULL)
		{
			if (g_vm->map[2][car->car_pos] != 1)
				g_vm->map[2][car->car_pos] = 1;
			if (car->comand == 0)
				vm_read_comand(car);
			else if (car->count == 0 && car->comand != 0)
				vm_make_move(car);
			else
				car->count--;
			car = car->next_car;
		}
		vm_make_game2(car);
		print_maps(); ///////////////////////////////
	}
}

void	vm_make_game2(t_car *car)
{
	if (++g_vm->cycle == g_vm->die_cycle)
		vm_car_to_die();
	car = g_vm->cars;
	while (car != NULL)
	{
		if (car->car_next_pos != 0)
			vm_car_next_pos(car);
		car = car->next_car;
	}
}

/*
** vm_game/2 - главная ф-ция запуска игры.
** 
** размещает ботов на карте. потом будет передавать это все дальше.
** еще пилю это.////////////////////////////////////////////////////////////////////
*/

void	vm_car_next_pos(t_car *car)
{
	if (car->car_next_pos < 1)
		return ;
	if (g_vm->map[2][car->car_pos] == 1)
		g_vm->map[2][car->car_pos] = 0;
	car->car_pos = ((car->car_pos + car->car_next_pos) % MEM_SIZE);
	if (g_vm->map[2][car->car_pos] != 1)
		g_vm->map[2][car->car_pos] = 1;
	car->car_next_pos = 0;
}

void	vm_car_to_die(void)
{
	t_car *tmp;
	t_car *start;

	start = g_vm->cars;
	while (start != NULL && start->live < 1)
	{
		tmp = start->next_car;
		free(start);
		g_vm->cars_nmbr -= 1;
		start = tmp;
	}
	g_vm->cars = start;
	if (g_vm->cars != NULL)
		vm_car_to_die2();
	else
		vm_finish_game();
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
