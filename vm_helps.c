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
	ft_putstr("\e[0;33m0x");
	if (ft_strlen(buf) == 3)
		ft_putstr("\e[0;33m0");
	else if (ft_strlen(buf) == 2)
		ft_putstr("\e[0;33m00");
	else if (ft_strlen(buf) == 1)
		ft_putstr("\e[0;33m000");
	ft_putstr(buf);
	ft_putstr("\e[1;31m : \e[0m");
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
		(ft_putstr_fd("\e[1;31mInvalid argument\e[0m", 2));
	else if (error == 2)
		ft_putstr_fd("\e[1;31mInvalid/empty file\e[0m", 2);
	else if (error == 3)
		ft_putstr_fd("\e[1;31mIncorrect champion\e[0m", 2);
	else if (error == 4)
		ft_putstr_fd("\e[1;31mChampion size too big. > CHAMP_MAX_SIZE\e[0m", 2);
	else if (error == 5)
		ft_putstr_fd("\e[1;32mNeed \\0 at end of champ name/comment\e[0m", 2);
	else if (error == 6)
		ft_putstr_fd("\e[1;33mChampion size != encoded size\e[0m", 2);
	else if (error == 7)
		ft_putstr_fd("\e[0;31mWe need a champion!\e[0m", 2);
	else if (error == 8)
		ft_putstr_fd("\e[1;34mUnknown flag of incorrect usage\e[0m", 2);
	else if (error == 9)
		ft_putstr_fd("\e[0;33mToo many champions\e[0m", 2);
	else if (error == 10)
		ft_putstr_fd("\e[1;37mDamp must be bigger than zero\e[0m", 2);
	else if (error == 11)
		ft_putstr_fd("\e[1;35mChamp must be < CHAMP_MAX_SIZE\e[0m", 2);
	ft_putstr_fd("\n", 2);
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
	ft_putstr("\e[1;36mUsage:\n./corewar [-flags] <champion1.cor> <...>\n");
	ft_putstr("\e[1;36mflags:\n-v - Visual mode\n-l - Show lives\n\e[0m");
	ft_putstr("\e[1;36m-n XXX - champ namber\n\e[0m");
	ft_putstr("\e[1;36m-damp XXX - print memory on XXX cycle\n\e[0m");
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
