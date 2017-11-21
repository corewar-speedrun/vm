/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ireva <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 17:55:08 by ireva             #+#    #+#             */
/*   Updated: 2017/11/20 10:03:59 by dmaznyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <stdlib.h>
#include <mach/mach_types.h>
#include "corewar.h"

void		print_cl_players(WINDOW *win[2])
{
	wattron(win[1], COLOR_PAIR(7));
	if (g_vm->flag > 0)
		with_comment(win);
	else
	{
		mvwprintw(win[1], 11, 16, "%s", g_vm->champs[1]->name);
		if (g_vm->champs_nmbr > 1)
		{
			wattron(win[1], COLOR_PAIR(8));
			mvwprintw(win[1], 15, 16, "%s", g_vm->champs[2]->name);
		}
		if (g_vm->champs_nmbr > 2)
		{
			wattron(win[1], COLOR_PAIR(6));
			mvwprintw(win[1], 19, 16, "%s", g_vm->champs[3]->name);
		}
		if (g_vm->champs_nmbr > 3)
		{
			wattron(win[1], COLOR_PAIR(9));
			mvwprintw(win[1], 23, 16, "%s", g_vm->champs[4]->name);
		}
	}
	wattroff(win[1], COLOR_PAIR(9));
	wrefresh(win[1]);
}

void		print_players(WINDOW *win[2])
{
	g_vm->flag = 0;
	print_f_player(win);
	if (g_vm->champs_nmbr > 1)
		print_s_player(win);
	if (g_vm->champs_nmbr > 2)
		print_th_player(win);
	if (g_vm->champs_nmbr > 3)
		print_fo_player(win);
	mvwprintw(win[1], 13 + (4 * (g_vm->champs_nmbr - 1)) +
			8, 6, "%s %d", "CYCLE_TO_DIE :", g_vm->to_die);
	mvwprintw(win[1], 13 + (4 * (g_vm->champs_nmbr - 1)) +
			10, 6, "%s %d", "CYCLE_DELTA :", CYCLE_DELTA);
	mvwprintw(win[1], 13 + (4 * (g_vm->champs_nmbr - 1)) +
			12, 6, "%s %d", "NBR_LIVE :", NBR_LIVE);
	mvwprintw(win[1], 13 + (4 *
		(g_vm->champs_nmbr - 1)) + 14, 6, "%s %d", "MAX_CHECKS :", MAX_CHECKS);
	print_cl_players(win);
}

void		print_window(WINDOW *win[2], int sleep)
{
	win[0] = newwin(68, 196, 0, 0);
	win[1] = newwin(68, 70, 0, 195);
	nodelay(win[1], TRUE);
	nodelay(win[0], TRUE);
	wattron(win[0], COLOR_PAIR(5));
	wborder(win[0], '*', '*', '*', '*', '*', '*', '*', '*');
	wattron(win[1], COLOR_PAIR(5));
	wborder(win[1], '*', '*', '*', '*', '*', '*', '*', '*');
	wattron(win[0], COLOR_PAIR(6));
	wattron(win[1], COLOR_PAIR(19));
	keypad(win[1], TRUE);
	mvwprintw(win[1], 2, 4, "%s   ", "** RUNNING **");
	mvwprintw(win[1], 4, 4, "%s   ", "Cycles/second limit :");
	mvwprintw(win[1], 7, 4, "%s %d", "Cycle :", g_vm->cycle);
	mvwprintw(win[1], 9, 4, "%s %d", "Processes :", g_vm->cars_nmbr);
	print_players(win);
	mvwprintw(win[1], 5, 27, "delay %d         ", sleep);
}

void		print_mem(WINDOW *win[2], int sleep)
{
	int y;
	int x;
	int i;

	y = 1;
	x = 0;
	i = 0;
	while (++y < 66)
	{
		x = 2;
		while (x < 194)
		{
			players_color(win, i);
			if (g_vm->map3[i] > 0)
				fnkg_shit(win, i);
			if (g_vm->map2[i] == 1)
				shit(win, i);
			mvwprintw(win[0], y, x, "%.2x", g_vm->map0[i]);
			x += 3;
			i++;
		}
		usleep((useconds_t)sleep);
	}
	wrefresh(win[0]);
	wrefresh(win[1]);
}

int			ncurses(int sleep)
{
	WINDOW	*win[2];

	init();
	noecho();
	print_window(win, sleep);
	print_mem(win, sleep);
	sleep = paused(win, sleep);
	return (sleep);
}
