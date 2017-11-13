/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_comands1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 15:07:20 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/13 15:07:24 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_car	*vm_com_live(t_car *car)
{
	unsigned char	tmp;
	int 			champ_namber;
	int 			z;

	z = -1;
	champ_namber = 0;
	while (++z < 4)
	{
		tmp = g_vm->map[0][car->car_pos + z];
		champ_namber = champ_namber << 8 | tmp;
	}
	if (champ_namber >= 1 && champ_namber <= g_vm->champs_nmbr)
	{
		g_vm->champs[champ_namber]->live += 1;
		g_vm->champs[champ_namber]->last_live = g_vm->cycle;
		if (g_vm->flag_say_alive == 1)
			vm_com_live2(champ_namber);
	}
	car->car_next_pos = 5;
	car->count = 0;
	car->comand = 0;
	car->live += 1;
	return (car);
}

void	vm_com_live2(int champ_namber)
{
	ft_putstr("Player \0");
	ft_putnbr(champ_namber);
	write(1, " (", 2);
	ft_putstr(g_vm->champs[champ_namber]->name);
	write(1, ") ", 2);
	ft_putstr("is said to be alive\n\0");	
}
