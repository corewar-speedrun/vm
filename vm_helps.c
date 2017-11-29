/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_helps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:22:02 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/20 09:39:36 by dmaznyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	align(int i)
{
	char	*buf;

	buf = ft_itoa_base(i, 16);
	ft_putstr("0x");
	if (ft_strlen(buf) == 3)
		ft_putstr("0");
	else if (ft_strlen(buf) == 2)
		ft_putstr("00");
	else if (ft_strlen(buf) == 1)
		ft_putstr("000");
	ft_putstr(buf);
	ft_putstr(" : ");
	ft_strdel(&buf);
}

void	print_maps(void)
{
	int		i;
	int		j;
	char	*buf2;

	i = 0;
	while (i < MEM_SIZE)
	{
		align(i);
		j = -1;
		while (++j < 64)
		{
			buf2 = ft_itoa_base(g_vm->map0[i], 16);
			if (ft_strlen(buf2) < 2)
				ft_putchar('0');
			ft_putstr(buf2);
			ft_putchar(' ');
			i++;
			ft_strdel(&buf2);
		}
		ft_putchar('\n');
	}
}

int		vm_error(int error)
{
	if (error == 1)
		return (vm_usage("Invalid argument.\n\0"));
	else if (error == 2)
		ft_putstr_fd("Invalid or empty file.\n\0", 2);
	else if (error == 3)
		ft_putstr_fd("Wrong Champion. Incorrect MAGIC.\n\0", 2);
	else if (error == 4)
		ft_putstr_fd("Champion size too big. > CHAMP_MAX_SIZE\n\0", 2);
	else if (error == 5)
		ft_putstr_fd("We need \\0 at the end of champ name or comment\n\0", 2);
	else if (error == 6)
		ft_putstr_fd("Champion size != encoded size by Assembler\n\0", 2);
	else if (error == 7)
		vm_usage("We need a champion!\n\0");
	else if (error == 8)
		vm_usage("Some unknown flag of incorrect usage\n\0");
	else if (error == 9)
		vm_usage("Too many champions\n\0");
	else if (error == 10)
		vm_usage("Damp must be bigger than zero\n\0");
	else if (error == 11)
		vm_usage("Champ must be smaller than CHAMP_MAX_SIZE\n\0");
	system("say YOU SHALL NOT PASS");
	return (0);
}

/*
** error management.
**
** error == 1 - invalid argument""
** error == 2 - invalid of empty file;
** error == 3 - wrong MAGIC;
** error == 4 - champion size > CHAMP_MAX_SIZE
** error == 5 - no \0 at the end of champion name or comment
** error == 6 - Champion size != encoded size by Assembler
** error == 7 - Wee need a champion > 0!
** error == 8 - Wrong flag
** error == 9 - Too many champions
** error == 10 - damp < 1;
*/

int		vm_usage(char *re)
{
	if (re != NULL)
		ft_putstr_fd(re, 2);
	ft_putstr("Usage:\n./corewar [-flags] <champion1.cor> <...>\n\0");
	ft_putstr("flags:\n-v - Visual mode\n-l - Show lives\n\0");
	ft_putstr("-damp NAMBER - print game memory on NAMBER cycle\n\0");
	return (0);
}

void	vm_car_next_pos(t_car *car)
{
	car->f_move = 1;
	if (car->car_next_pos == 0)
		return ;
	if (car->car_next_pos < 0)
		car->car_next_pos = (MEM_SIZE + car->car_next_pos) % MEM_SIZE;
	if (g_vm->map2[car->car_pos] == 1)
		g_vm->map2[car->car_pos] = 0;
	car->car_pos = ((car->car_pos + car->car_next_pos) % MEM_SIZE);
	if (g_vm->map2[car->car_pos] != 1)
		g_vm->map2[car->car_pos] = 1;
	car->car_next_pos = 0;
}
