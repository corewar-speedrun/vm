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

void	align(int i, int k)
{
	char	*buf;

	buf = ft_itoa_base(i - k, 16);
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
	int		k;
	char	*buf2;

	i = -1;
	k = 0;
	while (++i < MEM_SIZE)
	{
		align(i, k);
		j = -1;
		while (++j < 32 && i < MEM_SIZE)
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
		k++;
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
