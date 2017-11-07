/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:20:18 by dverbyts          #+#    #+#             */
/*   Updated: 2017/10/24 14:20:22 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		main(int i, char **arg)
{
	if (i < 2)
		return(vm_usage(NULL));
	if (!(g_vm = (t_vm *)malloc(sizeof(t_vm))))
		return (0);
	vm_init();
	vm_read(i, arg);
	if (g_vm->error != -1)
		return (vm_error(g_vm->error));
	vm_init_champs();
	vm_make_game();
}

void	vm_make_game(void)
{
	t_car *move;

	while (g_vm->game == 1)
	{
		move = g_vm->cars;
		while (move != NULL)
		{
			if (move->comand == 0)
				move = vm_read_comand(move);
			else if (move->count == 0 && move->comand != 0)
			{
				g_vm->map[2][move->car_pos] = 0;
				move = vm_make_move(move);
			}
			else
				move->count--;
			if (g_vm->map[2][move->car_pos] != 1)
				g_vm->map[2][move->car_pos] = 1;
			move = move->next_car;
		}
		if (++g_vm->cycle == g_vm->to_die)
			vm_to_die();
	}
}


/*
** vm_game - главная ф-ция запуска игры.
** 
** размещает ботов на карте. потом будет передавать это все дальше.
** еще пилю это.////////////////////////////////////////////////////////////////////
*/

t_car	*vm_make_move(t_car *move)
{
	if (move->comand == 0)
		move = vm_read_comand(move);
	else
	{
		move = vm_make_comand(move);
	}
	return (move);
}

t_car	*vm_read_comand(t_car *move)
{

}

void	vm_to_die(void)
{
	t_car *move;
	t_car *tmp;

	move = g_vm->cars;
	while (move != NULL)
	{
		if (move->live < 1)
		{
			tmp
		}
	}
}