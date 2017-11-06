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
	t_vm *vm;

	if (i < 2)
		return(vm_usage(NULL));
	vm = vm_init();
	vm_read(vm, i, arg);
	if (vm->error != -1)
		return (vm_error(vm->error));
	vm_init_champs(vm);
	vm_make_game(vm);
}

void	vm_game(t_vm *vm)
{
	t_car *move;

	while (vm->game == 1)
	{
		move = vm->cars;
		while (move != NULL)
		{
			if (move->count == 0)
				move = vm_make_move(vm, move);
			else
				move->count--;
			move = move->next_car;
		}
		if (++vm->cycle == vm->to_die)
			vm_to_die();
	}
}


/*
** vm_game - главная ф-ция запуска игры.
** 
** размещает ботов на карте. потом будет передавать это все дальше.
** еще пилю это.////////////////////////////////////////////////////////////////////
*/

t_car	vm_make_move(t_vm *vm, t_car *move)
{
	if (move->comand == 0)
		move = vm_read_comand(vm, move);
	else
	{
		move = vm_make_comand(vm, move);
	}
	return (move);
}