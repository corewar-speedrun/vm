/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_commands_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 16:24:08 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/13 16:24:11 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		vm_find_next_pos(t_car *car)
{
	int i;
	int r;
	int c_nmbr

	c_nmbr = car->comand;
	i = -1;
	r = 2;
	while (++i < 3)
	{
		if (car->c_byte[i] == 1)
			r += 1;
		else if (car->c_byte[i] == 2 && ((c_nmbr >= 1 && c_nmbr <= 8) ||
			c_nmbr == 13 || c_nmbr == 16))
			r += 4;
		else if (car->c_byte[i] == 2 && ((c_nmbr >= 9 && c_nmbr <= 12) ||
			c_nmbr == 14 || c_nmbr == 15))
			r += 2;
		else if (car->c_byte[i] == 3)
			r += 2;
	}
	return (r);
}

void	vm_car_clean(t_car *car)
{
	int i;

	i = -1;
	while (++i < 3)
	{
		car->c_byte[i] = 0;
		car->com_args[i] = 0;
	}
	car->count = 0;
	car->comand = 0;
}

void		vm_parse_code_byte(t_car *car)
{
	unsigned char	code_byte;

	code_byte = g_vm->map[0][car->car_pos + 1];
	car->c_byte[0] = (code_byte << 4) >> 6;
	car->c_byte[1] = (code_byte << 2) >> 6;
	car->c_byte[2] = code_byte >> 6;
}

int		vm_get_arg(t_car *car, int arg, int i)
{
	if (car->c_byte[arg] == 1)
		return (vm_get_t_reg(car, arg, i));
	else if (car->c_byte[arg] == 2)
		return (vm_get_t_dir(car, arg, i));
	else if (car->c_byte[arg] == 3)
		return (vm_get_t_ind(car, arg, i));
	return (0);
}

// void		vm_get_arg_un(t_car *car, int args)
// {
// 	unsigned char	tmp;
// 	int z;
// 	int r;

// 	z = -1;
// 	r = 0;

// 	while (++z < size)
// 	{
// 		tmp = g_vm->map[0][car->car_pos + (read_position + z)];
// 		r = (r << 8) | tmp;
// 	}
// 	return (r);
// }

