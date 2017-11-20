/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_norma.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ireva <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 17:36:52 by ireva             #+#    #+#             */
/*   Updated: 2017/11/20 17:37:08 by ireva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_f_player(WINDOW *win[2])
{
	mvwprintw(win[1], 11, 4, "%s", "Player -1 :");
	mvwprintw(win[1], 12, 6, "%s %d",
			"Last live :", g_vm->champs[1]->last_live);
	mvwprintw(win[1], 13, 6, "%s %d",
			"Lives in current period :", g_vm->champs[1]->live);
	if (g_vm->champs[1]->comment != NULL)
	{
		mvwprintw(win[1], 11 + 3 + g_vm->flag, 4, "%s %s", "Comment :",
				g_vm->champs[1]->comment);
		g_vm->flag++;
	}
}

void	print_s_player(WINDOW *win[2])
{
	mvwprintw(win[1], 15 + g_vm->flag, 4, "%s", "Player -2 :");
	mvwprintw(win[1], 16 + g_vm->flag, 6, "%s %d",
			"Last live :", g_vm->champs[2]->last_live);
	mvwprintw(win[1], 17 + g_vm->flag, 6, "%s %d",
			"Lives in current period :", g_vm->champs[2]->live);
	if (g_vm->champs[2]->comment != NULL)
	{
		mvwprintw(win[1], 15 + 3 + g_vm->flag, 4, "%s %s", "Comment :",
			g_vm->champs[2]->comment);
		g_vm->flag++;
	}
}

void	print_th_player(WINDOW *win[2])
{
	mvwprintw(win[1], 19 + g_vm->flag, 4, "%s", "Player -3 :");
	mvwprintw(win[1], 20 + g_vm->flag, 6, "%s %d",
		"Last live :", g_vm->champs[3]->last_live);
	mvwprintw(win[1], 21 + g_vm->flag, 6, "%s %d",
		"Lives in current period :", g_vm->champs[3]->live);
	if (g_vm->champs[3]->comment != NULL)
	{
		mvwprintw(win[1], 19 + 3 + g_vm->flag, 4, "%s %s", "Comment :",
			g_vm->champs[3]->comment);
		g_vm->flag++;
	}
}

void	print_fo_player(WINDOW *win[2])
{
	mvwprintw(win[1], 23 + g_vm->flag, 4, "%s", "Player -4 :");
	mvwprintw(win[1], 24 + g_vm->flag, 6, "%s %d",
			"Last live :", g_vm->champs[4]->last_live);
	mvwprintw(win[1], 25 + g_vm->flag, 6, "%s %d",
			"Lives in current period :", g_vm->champs[4]->live);
	if (g_vm->champs[4]->comment != NULL)
	{
		mvwprintw(win[1], 23 + 3 + g_vm->flag, 4, "%s %s", "Comment :",
			g_vm->champs[4]->comment);
		g_vm->flag++;
	}
}

void	players_color(WINDOW *win[2], int i)
{
	if (g_vm->map1[i] == 1)
		wattron(win[0], COLOR_PAIR(7));
	else if (g_vm->map1[i] == 2)
		wattron(win[0], COLOR_PAIR(8));
	else if (g_vm->map1[i] == 3)
		wattron(win[0], COLOR_PAIR(6));
	else if (g_vm->map1[i] == 4)
		wattron(win[0], COLOR_PAIR(9));
	else
		wattron(win[0], COLOR_PAIR(10));
	wrefresh(win[1]);
}
