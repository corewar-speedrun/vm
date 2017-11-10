/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_game2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 08:46:17 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/10 08:46:20 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_car	*vm_read_comand(t_car *move)
{
	unsigned char tmp;

	tmp = g_vm->map[0][move->car_pos];
	if (tmp > 0 && tmp < 17)
	{
		move->comand = (int)tmp;
		move->count = vm_cycles_lib((int)tmp);
		if (move->comand == 1)
			move->live = 1;
	}
	else
		move->car_next_pos += 1;
	return (move);
}

t_car	*vm_make_move(t_car *move)
{
	// g_vm->map[2][move->car_pos] = 0;
	// if (move->comand == 1)
	// 	move = vm_com_live(move);
	// else if (move->comand == 2)
	// 	move = vm_com_ld(move);
	// else if (move->comand == 3)
	// 	move = vm_com_st(move);
	// else if (move->comand == 4)
	// 	move = vm_com_add(move);
	// else if (move->comand == 5)
	// 	move = vm_com_sub(move);
	// else if (move->comand == 6)
	// 	move = vm_com_and(move);
	// else if (move->comand == 7)
	// 	move = vm_com_or(move);
	// else if (move->comand == 8)
	// 	move = vm_com_xor(move);
	// else
	// 	move = vm_make_move2(move);
	// if (move->car_next_pos == 0) ///////////////////////////////////////////////////////////
	// 	move->car_next_pos += 1;
	return (move);
}

t_car	*vm_make_move2(t_car *move)
{
	// if (move->comand == 9)
	// 	move = vm_com_zjmp(move);
	// else if (move->comand == 10)
	// 	move = vm_com_ldi(move);
	// else if (move->comand == 11)
	// 	move = vm_com_sti(move);
	// else if (move->comand == 12)
	// 	move = vm_com_fork(move);
	// else if (move->comand == 13)
	// 	move = vm_com_lld(move);
	// else if (move->comand == 14)
	// 	move = vm_com_lldi(move);
	// else if (move->comand == 15)
	// 	move = vm_com_ifork(move);
	// else if (move->comand == 16)
	// 	move = vm_com_aff(move);
	// else
	// 	ft_putstr_fd("Some unknow error.\n\0", 2);
	return (move);
}



int		vm_cycles_lib(int tmp)
{
	if (tmp == 16)
		return (2);
	else if (tmp == 2 || tmp == 3)
		return (5);
	else if (tmp >= 6 && tmp <= 8)
		return (6);
	else if (tmp == 1 || tmp == 4 || tmp == 5 || tmp == 13)
		return (10);
	else if (tmp == 9)
		return (20);
	else if (tmp == 10 || tmp == 11)
		return (25);
	else if (tmp == 14)
		return (50);
	else if (tmp == 12)
		return (800);
	else if (tmp == 15)
		return (1000);
	return (0);
}
