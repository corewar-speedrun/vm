/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 19:43:58 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/01 19:43:59 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_vm			*vm_init(void)
{
	t_vm			*mem;
	int 			i;

	i = -1;
	if (!(mem = (t_vm *)malloc(sizeof(t_vm) * 1)))
		return (NULL);
	ft_bzero(mem, sizeof(t_vm));
	mem->champs = (t_champ **)malloc(sizeof(t_champ *) * MAX_PLAYERS); //////////////////// потестить 3 или 4 должно тут быть
	while (++i < MAX_PLAYERS)
		mem->champs[i] = NULL;
	mem->error = -1;
	mem->champs_nmbr = -1;
	mem->map = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE);
	ft_bzero(mem->map, (sizeof(unsigned char) * MEM_SIZE));
	return (mem);
}

/*
** vm_init - выделяем память под основную структуру виртуальной машины - t_vm.
*/

unsigned char	*vm_init_game(t_vm *vm)
{
	unsigned char	*map;
	int				i;
	int				q;
	int				w;

	map = vm->map;
	q = -1;
	while (vm->champs[++q] != NULL)
	{
		if (q == 0)
		{
			i = -1;
			while (++i < vm->champs[q]->size)
				map[i] = vm->champs[q]->src[i];
		}
		else
		{
			w = (MEM_SIZE / vm->champs_nmbr) * (q + 1);
			i = -1;
			while (++i < vm->champs[q]->size)
				map[w++] = vm->champs[q]->src[i];
		}
	}
	return (map);
}
