/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:20:18 by dverbyts          #+#    #+#             */
/*   Updated: 2017/10/24 14:20:22 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		main(int i, char **arg)
{
	t_vm *vm;

	if (i < 2)
		return(vm_usage(NULL));
	vm = vm_init();
	vm_read(vm, i, arg);
	if (vm->error != -1)
		return (vm_error(vm->error));
	vm_make_game(vm);
}

int		vm_error(int error)
{
	if (error == 1)
		return(vm_usage("Invalid argument.\n\0"));
	else if (error == 2)
		ft_putstr("Invalid or empty file.\n\0");
	else if (error == 3)
		ft_putstr("Wrong MAGIC.\n\0");	
	else if (error == 4)
		ft_putstr("Champion size too big. > CHAMP_MAX_SIZE\n\0");
	else if (error == 5)
		ft_putstr("We need \\0 at the end of champion name or comment\n\0");
	else if (error == 6)
		ft_putstr("Champion size error. Size != encoded size by Assembler\n\0");
	else if (error == 7)
		vm_usage("We need a champion!\n\0");
	else
		ft_putstr("Some unknow error.\n\0");
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
*/

int		vm_usage(char *re)
{
	if (re != NULL)
		ft_putstr(re);
	ft_putstr("Usage:\n./corewar [-flags] <champion1.cor> <...>\n\0");
	return (0);
}

void	vm_make_game(t_vm *vm)
{
	vm_init_champs(vm);
	int i = -1;
	int z = 1;
	while (++i < MEM_SIZE)
	{
		printf("|%x| ", vm->map[0][i]);
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
		printf("|%x| ", vm->map[1][i]);
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
		printf("|%x| ", vm->map[2][i]);
		if (z % 4 == 0)
			printf("  ");
		if (z % 32 == 0)
			printf("\n");
		z++;
	}
}

/*
** vm_make_game - главная ф-ция запуска игры.
** 
** размещает ботов на карте. потом будет передавать это все дальше.
** еще пилю это.////////////////////////////////////////////////////////////////////
*/
