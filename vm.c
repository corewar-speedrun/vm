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
}


t_vm	*vm_init(void)
{
	t_vm	*mem;
	int 	i;

	i = -1;
	if (!(mem = (t_vm *)malloc(sizeof(t_vm) * 1)))
		return (NULL);
	ft_bzero(mem, sizeof(t_vm));
	mem->champs = (t_champ **)malloc(sizeof(t_champ *) * MAX_PLAYERS); //////////////////// потестить 3 или 4 должно тут быть
	while(++i < MAX_PLAYERS)
		mem->champs[i] = NULL;
	mem->error = -1;
	mem->champs_nmbr = -1;
	mem->game = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE + 1);
	ft_bzero(mem->game, (sizeof(unsigned char) * MEM_SIZE + 1));
	return (mem);
}

/*
** vm_init - создаем основную структуру виртуальной машины - t_vm и выделяем под нее память.
*/


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
	else if (error == 4)
		ft_putstr("We need \0 at the end of champion name or comment\n\0");
	else
		ft_putstr("Some unknow error.\n\0");
	return (0);
}

/*
** error management.
**
** error = 1 - invalid argument""
** error = 2 - invalid of empty file;
** error = 3 - wrong MAGIC;
** error = 4 - champion size > CHAMP_MAX_SIZE
** error = 5 - no \0 at the end of champion name or comment
*/

int		vm_usage(char *re)
{
	if (re != NULL)
		ft_putstr(re);
	ft_putstr("Usage:\n./corewar [-flags] <champion1.cor> <...>\n\0");
	return (0);
}

