/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:20:18 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/12 20:54:39 by nsharova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int i, char **arg)
{
	int z;
	int sleep;

	sleep = 10000;
	z = 0;
	if (i < 2)
		return(vm_usage(NULL));
	if (!(g_vm = (t_vm *)malloc(sizeof(t_vm))))
		return (0);
	vm_init();
	vm_read(i, arg);
	if (g_vm->error != -1)
		return (vm_error(g_vm->error));
	vm_init_champs();
	if (g_vm->flag_visualize == 1)
	{
		while (z < 2147483646)
            sleep = ncurses(++z, sleep);
	}
	else
	{
		print_maps();
	//	vm_make_game(NULL);
	}
	return (0);
}
