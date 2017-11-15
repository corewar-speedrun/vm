/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_commands3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 17:22:52 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/15 17:22:55 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_com_aff(t_car *car)
{
	int tmp;
	char a;

	car->carry = FALSE;
	vm_get_reg_dir(car, 0, 2);
	if (car->c_byte[1] == 1 && car->com_args[0] > 0 && car->com_args[0] < 17)
	{
		tmp = car->car_reg[car->com_args[0]];
		while (tmp > 0)
		{
			a = tmp % 256;
			write (1, &a, 1);
			tmp = tmp / 256;
		}
		car->carry = TRUE;
	}
	car->car_next_pos = vm_find_next_pos(car);
	vm_car_clean(car);
}

T_REG | T_DIR | T_IND	T_DIR | T_REG	T_REG

складываеся значение в аргументе 1 и аргументе 2 и значение % IDX_MOD 
по полученному индеку записывается в аргумент 3 (загрузка в регистр)

((а1 + а2) % IDX_MOD) по полученному индеку считывает 4байта  и 
значение записывает в а3. Может сдвигаться назад (негативный сдвиг)

• ldi: ldi, ldi, as per the name, does not imply to go swimming in chestnut cream,
even if its code is 0x0a. Instead, it will use 2 indexes and 1 registry, adding 
the first
two, treating that like an address, reading a value of a registry’s size and putting
it on the third.

This operation modifies the carry. ldi 3,%4,r1 reads IND_SIZE
bytes at address: (PC + (3 % IDX_MOD)), adds 4 to this value.
We will name this sum S. Read REG_SIZE bytes at address (PC
+ (S % IDX_MOD)), which are copied to r1. Parameters 1 and 2
are indexes.

void				vm_com_ldi(t_car *car)
{
	int i;

	i = 2;
	car->carry = FALSE;
	if ((car->c_byte[1] == 1 || car->c_byte[1] == 2) && car->c_byte[2] == 1)
	{
		if (car->c_byte[1] == 3)
			vm_get_ind(car, 0, i);
		else
			vm_get_reg_dir(car, 0, i);
		if (car->c_byte[0] == 1)
			i +=1;
		else
			i +=2;
		vm_get_reg_dir(car, 1, i);
		if (car->c_byte[1] == 1)
			i +=1;
		else
			i +=2;
		vm_get_reg_dir(car, 2, i);
		car->carry = TRUE;
	}
	car->car_next_pos = vm_find_next_pos(car);
	vm_car_clean(car);
}

void				vm_com_ldi2(t_car *car)
{

}
