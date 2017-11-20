/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 17:30:23 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/20 17:30:27 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		vm_check_numbers(int i, int j)
{
	int flag;

	while (++i < 5)
	{
		j = 0;
		flag = 0;
		while (++j < 5)
		{
			if (g_vm->nambering[j] == i)
				flag += 1;
			if (flag > 1 || g_vm->nambering[j] > g_vm->champs_nmbr)
			{
				g_vm->error = 8;
				return (0);
			}
		}
	}
	return (1);
}

void	vm_split_champs(void)
{
	int		f;
	int		i;
	t_champ	*tmp;

	i = 0;
	f = 1;
	!vm_check_numbers(0, 0) ? (f = 0) : 0;
	if (f)
	{
		while (++i < 5)
		{
			if (g_vm->nambering[i] != i && g_vm->nambering[i] != 0
				&& i < g_vm->nambering[i])
			{
				tmp = g_vm->champs[i];
				if (tmp == NULL)
				{
					g_vm->error = 8;
					return ;
				}
				g_vm->champs[i] = g_vm->champs[g_vm->nambering[i]];
				g_vm->champs[g_vm->nambering[i]] = tmp;
			}
		}
	}
}
