/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ireva <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 18:19:18 by ireva             #+#    #+#             */
/*   Updated: 2017/11/20 18:20:10 by ireva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		key_managment(int ch, int sleep)
{
	(ch == KEY_UP && sleep != 0) ? sleep -= 1000 : 0;
	(sleep <= 0) ? sleep = 1 : 0;
	(ch == KEY_DOWN && sleep != 0) ? sleep += 1000 : 0;
	(ch == 'q') ? exit(0) : 0;
	return (sleep);
}
