/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 19:43:58 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/20 09:50:08 by dmaznyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_init(int i)
{
	ft_bzero(g_vm, sizeof(*g_vm));
	g_vm->champs = (t_champ **)malloc(sizeof(t_champ *) * (MAX_PLAYERS + 1));
	while (++i < MAX_PLAYERS + 1)
		g_vm->champs[i] = NULL;
	g_vm->error = -1;
	g_vm->map0 = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE);
	ft_bzero(g_vm->map0, (sizeof(unsigned char) * MEM_SIZE));
	g_vm->map1 = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE);
	ft_bzero(g_vm->map1, (sizeof(unsigned char) * MEM_SIZE));
	g_vm->map2 = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE);
	ft_bzero(g_vm->map2, (sizeof(unsigned char) * MEM_SIZE));
	g_vm->map3 = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE);
	ft_bzero(g_vm->map3, (sizeof(unsigned char) * MEM_SIZE));
	g_vm->damp = -1;
	g_vm->game = 1;
	g_vm->move = 1;
	g_vm->to_die = CYCLE_TO_DIE;
	g_vm->die_cycle = g_vm->to_die;
	g_vm->max_live_checks = MAX_CHECKS;
	g_vm->sleep = 1;
}

/*
** vm_init - выделяем память под основную структуру виртуальной машины - t_vm.
*/

void	vm_init_champs(void)
{
	int				i;
	int				q;
	int				w;

	q = 0;
	while (++q <= g_vm->champs_nmbr)
	{
		w = (MEM_SIZE / g_vm->champs_nmbr) * (q - 1);
		g_vm->map2[w] = 1;
		vm_init_car(w, 0, g_vm->champs[q]->nmbr, NULL);
		i = -1;
		while (++i < g_vm->champs[q]->size)
		{
			g_vm->map0[w] = g_vm->champs[q]->src[i];
			g_vm->map1[w++] = q;
		}
	}
}

/*
** vm_init_champs - копирует исходный код ботов и размещает на карте.
*/

void	vm_init_car(int pos, int next, int champ_nmbr, t_car *car)
{
	t_car *mem;

	if (!(mem = (t_car *)malloc(sizeof(t_car))))
		return ;
	ft_bzero(mem, sizeof(t_car));
	g_vm->cars_nmbr += 1;
	mem->car_reg[1] = champ_nmbr * -1;
	mem->car_reg[0] = champ_nmbr * -1;
	mem->car_pos = pos;
	mem->car_next_pos = next;
	if (mem->car_next_pos != 0)
		vm_car_next_pos(mem);
	if (car != NULL)
	{
		next = -1;
		while (++next <= (REG_NUMBER + 1))
			mem->car_reg[next] = car->car_reg[next];
	}
	mem->next_car = (g_vm->cars == NULL) ? NULL : g_vm->cars;
	mem->carry = (car == NULL) ? FALSE : car->carry;
	mem->live = (car == NULL) ? FALSE : car->live;
	mem->nabr = g_vm->cars_nmbr;
	(car != NULL) ? vm_read_comand(mem) : 0;
	(car != NULL) ? mem->count-- : 0;
	g_vm->cars = mem;
}

void	vm_map_write(int c, int p, t_car *car)
{
	if (p < 0)
		p = (MEM_SIZE + p) % MEM_SIZE;
	g_vm->map0[p % MEM_SIZE] = (c >> 24) & 255;
	g_vm->map0[(p + 1) % MEM_SIZE] = (c >> 16) & 255;
	g_vm->map0[(p + 2) % MEM_SIZE] = (c >> 8) & 255;
	g_vm->map0[(p + 3) % MEM_SIZE] = c & 255;
	g_vm->map1[p % MEM_SIZE] = car->car_reg[0] * -1;
	g_vm->map1[(p + 1) % MEM_SIZE] = car->car_reg[0] * -1;
	g_vm->map1[(p + 2) % MEM_SIZE] = car->car_reg[0] * -1;
	g_vm->map1[(p + 3) % MEM_SIZE] = car->car_reg[0] * -1;
	g_vm->map3[p % MEM_SIZE] = 1;
	g_vm->map3[(p + 1) % MEM_SIZE] = 1;
	g_vm->map3[(p + 2) % MEM_SIZE] = 1;
	g_vm->map3[(p + 3) % MEM_SIZE] = 1;
}
