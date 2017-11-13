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

int		vm_find_next_pos(t_car *car, int args)
{

	return (2);
}

t_car		*vm_parse_code_byte(t_car *car)
{
	unsigned char	code_byte;

	code_byte = g_vm->map[0][car->car_pos + 1];
	car->c_byte[0] = (code_byte << 4) >> 6;
	car->c_byte[1] = (code_byte << 2) >> 6;
	car->c_byte[2] = code_byte >> 6;
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
