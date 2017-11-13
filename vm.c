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
	if (i < 2)
		return(vm_usage(NULL));
	if (!(g_vm = (t_vm *)malloc(sizeof(t_vm))))
		return (0);
	vm_init();
	vm_read(i, arg);
	if (g_vm->error != -1)
		return (vm_error(g_vm->error));
	vm_init_champs();
	print_maps();
	//vm_make_game(NULL);
	 return (0);
}



t_car		*vm_com_add(t_car *car)
{
	unsigned char	tmp1;
	unsigned char	tmp2;
	unsigned char	tmp3;

	tmp1 = g_vm->map[0][car->car_pos + 2];
	tmp2 = g_vm->map[0][car->car_pos + 3];
	tmp3 = g_vm->map[0][car->car_pos + 4];
	if (tmp1 >= 0 && tmp1 < 16 && tmp2 >= 0 && tmp2 < 16 && tmp3 >= 0 &&
		tmp3 < 16)
	{
		car->car_reg[tmp3] = car->car_reg[tmp1] + car->car_reg[tmp2];
		car->carry = 1;
	}
	else
		car->carry = 0;
	car->car_next_pos = 5;
	car->count = 0;
	car->comand = 0;
	return (car);
}

t_car		*vm_com_sub(t_car *car)
{
	unsigned char	tmp1;
	unsigned char	tmp2;
	unsigned char	tmp3;

	tmp1 = g_vm->map[0][car->car_pos + 2];
	tmp2 = g_vm->map[0][car->car_pos + 3];
	tmp3 = g_vm->map[0][car->car_pos + 4];
	if (tmp1 >= 0 && tmp1 < 16 && tmp2 >= 0 && tmp2 < 16 && tmp3 >= 0 &&
		tmp3 < 16)
	{
		car->car_reg[tmp3] = car->car_reg[tmp1] - car->car_reg[tmp2];
		car->carry = 1;
	}
	else
		car->carry = 0;
	car->car_next_pos = 5;
	car->count = 0;
	car->comand = 0;
	return (car);
}


t_car		*vm_parse_code_byte(t_car *car)
{
	char			*arg;
	unsigned char	code_byte;

	code_byte = g_vm->map[0][car->car_pos + 1];
	car->code_byte[0] = (code_byte << 4) >> 6;
	car->code_byte[1] = (code_byte << 2) >> 6;
	car->code_byte[2] = code_byte >> 6;
	return (car);


	// if (tmp != REG_CODE)
	// 	//kommanda ne vipolitsa
	// tmp = (code_byte << 2) >> 6;
	// if (tmp == DIR_CODE)
	// 	//do it
	// else if (tmp == IND_CODE)
	// 	//do it
	// else if (tmp == REG_CODE)
	// 	//do it
	// tmp = code_byte >> 6;
	// if (tmp == DIR_CODE)
	// 	//do it
	// else if (tmp == IND_CODE)
	// 	//do it
	// else if (tmp == REG_CODE)

}

