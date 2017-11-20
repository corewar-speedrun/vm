/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:20:18 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/20 09:22:22 by dmaznyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
t_vm		*g_vm;
  
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
	kakatofn();
	if (g_vm->error != -1)
		return (vm_error(g_vm->error));
	vm_init_champs();
	vm_make_game(NULL);
	return (0);
}

int		check_numbers(int i, int j)
{
	while (++i < 5)
	{
		j = 0;
		while (++j < 5)
			if (g_vm->nambering[i] == g_vm->nambering[j])
			{
				g_vm->error = 8;
				return (0);
			}
	}
	return (1);
}

void	kakatofn(void)
{
	int		f;
	int		i;
	t_champ	*tmp;

	i = 0;
	f = 1;
	!check_numbers(0, 0) ? (f = 0) : 0;
	if (f)
	{
		while (++i < 5)
		{
			if (g_vm->nambering[i] != i)
			{
				tmp = g_vm->champs[g_vm->nambering[i]];
				g_vm->champs[i] = g_vm->champs[g_vm->nambering[i]];
				g_vm->champs[g_vm->nambering[i]] = tmp;
				free(tmp);
			}
		}
	}
}