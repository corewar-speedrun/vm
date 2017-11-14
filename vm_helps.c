/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_helps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:22:02 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/06 16:22:04 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_maps(void) ////////////////////////////////\\\\\\\\\\\\\\\\\\\\\ del 
{
	int i = -1;
	int z = 1;
	while (++i < MEM_SIZE)
	{
		printf("|%x| ", g_vm->map[0][i]);
		if (z % 4 == 0)
			printf("  ");
		if (z % 32 == 0)
			printf("\n");
		z++;
	}
	i = -1;
	z = 1;
	printf("champs\n");
	while (++i < MEM_SIZE)
	{
		printf("|%x| ", g_vm->map[1][i]);
		if (z % 4 == 0)
			printf("  ");
		if (z % 32 == 0)
			printf("\n");
		z++;
	}
	printf("caretki\n");
	i = -1;
	z = 1;
	while (++i < MEM_SIZE)
	{
		printf("|%x| ", g_vm->map[2][i]);
		if (z % 4 == 0)
			printf("  ");
		if (z % 32 == 0)
			printf("\n");
		z++;
	}
}

int		vm_error(int error)
{
	if (error == 1)
		return(vm_usage("Invalid argument.\n\0"));
	else if (error == 2)
		ft_putstr_fd("Invalid or empty file.\n\0", 2);
	else if (error == 3)
		ft_putstr_fd("Wrong MAGIC.\n\0", 2);
	else if (error == 4)
		ft_putstr_fd("Champion size too big. > CHAMP_MAX_SIZE\n\0", 2);
	else if (error == 5)
		ft_putstr_fd("We need \\0 at the end of champion name or comment\n\0", 2);
	else if (error == 6)
		ft_putstr_fd("Champion size error. Size != encoded size by Assembler\n\0", 2);
	else if (error == 7)
		vm_usage("We need a champion!\n\0");
	else if (error == 8)
		vm_usage("Some unknown flag\n\0");
	else
		ft_putstr_fd("Some unknow error.\n\0", 2);
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
*/

int		vm_usage(char *re)
{
	if (re != NULL)
		ft_putstr_fd(re, 2);
	ft_putstr("Usage:\n./corewar [-flags] <champion1.cor> <...>\n\0");
	ft_putstr("-v - visual mode\n\0");
	return (0);
}

