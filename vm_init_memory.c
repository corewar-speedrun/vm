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
	mem->map = (unsigned char **)malloc(sizeof(unsigned char *) * 4);
	i = -1;
	while (++i < 4)
	{
		mem->map[i] = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE);
		ft_bzero(mem->map[i], (sizeof(unsigned char) * MEM_SIZE));
	}
	return (mem);
}

/*
** vm_init - выделяем память под основную структуру виртуальной машины - t_vm.
*/

void		vm_init_champs(t_vm *vm)
{
	int				i;
	int				q;
	int				w;

	q = -1;
	while (vm->champs[++q] != NULL)
	{
		w = (MEM_SIZE / (vm->champs_nmbr)) * q;
		vm->map[2][w] = 1;
		i = -1;
		while (++i < vm->champs[q]->size)
		{
			vm->map[0][w] = vm->champs[q]->src[i];
			vm->map[1][w++] = q + 1;
		}
	}
	return ;
}

/*
** vm_init_champs - копирует исходный код ботов и размещает на карте.
**
** еще пилю это.//////////////////////////////////////////////////////////////////////
*/

t_car		*vm_init_car(t_vm *vm)
{

}
