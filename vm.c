/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:20:18 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/19 18:36:29 by nsharova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
<<<<<<< HEAD
t_vm		*g_vm;
=======
t_vm	*g_vm;
>>>>>>> fd1da773baea34fc34d8d665bd753ad8a7f0d985

int		main(int i, char **arg)
{
	if (i < 2)
		return (vm_usage(NULL));
	if (!(g_vm = (t_vm *)malloc(sizeof(t_vm))))
		return (0);
	vm_init();
	vm_read1(i, arg, 0, 0);
	if (g_vm->error != -1)
		return (vm_error(g_vm->error));
	vm_init_champs();
	vm_make_game(NULL);
	return (0);
}
