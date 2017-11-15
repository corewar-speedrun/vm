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

#include "corewar.h"

void			vm_init(void)
{
	int 			i;

	i = -1;
	ft_bzero(g_vm, sizeof(g_vm));
	g_vm->champs = (t_champ **)malloc(sizeof(t_champ *) * (MAX_PLAYERS + 1));
	while (++i < MAX_PLAYERS + 1)
		g_vm->champs[i] = NULL;
	g_vm->error = -1;
	g_vm->map = (unsigned char **)malloc(sizeof(unsigned char *) * 4);
	i = -1;
	while (++i < 4)
	{
		g_vm->map[i] = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE);
		ft_bzero(g_vm->map[i], (sizeof(unsigned char) * MEM_SIZE));
	}
	g_vm->damp = -1;
	g_vm->game = 1;
	g_vm->to_die = CYCLE_TO_DIE;
	g_vm->die_cycle = g_vm->to_die; 
	return ;
}

/*
** vm_init - выделяем память под основную структуру виртуальной машины - t_vm.
*/

void		vm_init_champs(void)
{
	int				i;
	int				q;
	int				w;

	q = 0;
	while (g_vm->champs[++q] != NULL)
	{
		w = (MEM_SIZE / (g_vm->champs_nmbr)) * (q - 1);
		g_vm->map[2][w] = 1;
		vm_init_car(w, 0, g_vm->champs[q]->nmbr, NULL);
		i = -1;
		while (++i < g_vm->champs[q]->size)
		{
			g_vm->map[0][w] = g_vm->champs[q]->src[i];
			g_vm->map[1][w++] = q;
		}
	}
}

/*
** vm_init_champs - копирует исходный код ботов и размещает на карте.
**
** еще пилю это.//////////////////////////////////////////////////////////////////////
*/

void		vm_init_car(int pos, int next, int champ_nmbr, t_car *car)
{
	t_car *mem;

	if (!(mem = (t_car *)malloc(sizeof(t_car))))
		return ;
	ft_bzero(mem, sizeof(t_car));
	mem->car_reg[1] = champ_nmbr * -1;
	mem->car_pos = pos;
	mem->car_next_pos = next;
	if (mem->car_next_pos != 0)
			vm_car_next_pos(mem);
	if (car != NULL)
	{
		mem->live = car->live;
		mem->carry = car->carry;
		next = -1;
		while (++next < (REG_NUMBER + 2))
			mem->car_reg[next] = car->car_reg[next];
	} 
	mem->next_car = (g_vm->cars == NULL) ? NULL : g_vm->cars;
	mem->carry = FALSE;
	mem->live = (car == NULL) ? FALSE : car->live;
	g_vm->cars = mem;
	g_vm->cars_nmbr += 1;
}
