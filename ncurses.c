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

int			paused(WINDOW *win[2], int sleep)
{
	int	ch;

	ch = wgetch(win[1]);
	if (ch == ' ' || g_vm->move == 1)
	{
		mvwprintw(win[1], 2, 4, "%s   ", "** PAUSED **");
		wrefresh(win[1]);
		g_vm->move = 1;
		while (g_vm->move == 1)
		{
			ch = wgetch(win[1]);
			if (ch == ' ')
			{
				mvwprintw(win[1], 2, 4, "%s   ", "** RUNNING **");
				wrefresh(win[1]);
				g_vm->move--;
			}
			if (ch == KEY_RIGHT)
				break ;
		}
	}
	(ch == KEY_UP && sleep != 0) ? sleep -= 1000 : 0;
	(sleep <= 0) ? sleep = 1 : 0;
	(ch == KEY_DOWN && sleep != 0) ? sleep += 1000 : 0;
	(ch == 'q') ? exit(0) : 0;
	return (sleep);
}

void		players_color(WINDOW *win[2], int i)
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

void		print_cl_players(WINDOW *win[2], int flag)
{
	wattron(win[1], COLOR_PAIR(7));
	mvwprintw(win[1], 11, 16, "%s", g_vm->champs[1]->name);
	if (g_vm->champs_nmbr > 1)
	{
		wattron(win[1], COLOR_PAIR(8));
		if (flag > 0)
		{
			mvwprintw(win[1], 15 + 1, 16, "%s", g_vm->champs[2]->name);
			flag--;
		}
		else
			mvwprintw(win[1], 15, 16, "%s", g_vm->champs[2]->name);
	}
	if (g_vm->champs_nmbr > 2)
	{
		wattron(win[1], COLOR_PAIR(6));
		if (flag > 0)
		{
			mvwprintw(win[1], 19 + 2, 16, "%s", g_vm->champs[3]->name);
			flag--;
		}
		else
			mvwprintw(win[1], 19, 16, "%s", g_vm->champs[3]->name);
	}
	if (g_vm->champs_nmbr > 3)
	{
		wattron(win[1], COLOR_PAIR(9));
		if (flag > 0)
			mvwprintw(win[1], 23 + 3, 16, "%s", g_vm->champs[4]->name);
		else
			mvwprintw(win[1], 23, 16, "%s", g_vm->champs[4]->name);
	}
	wattroff(win[1], COLOR_PAIR(9));
	wrefresh(win[1]);
}

void		print_players(WINDOW *win[2])
{
	int	flag;

	flag = 0;
	mvwprintw(win[1], 11, 4, "%s", "Player -1 :");
	mvwprintw(win[1], 12, 6, "%s %d",
			"Last live :", g_vm->champs[1]->last_live);
	mvwprintw(win[1], 13, 6, "%s %d",
			"Lives in current period :", g_vm->champs[1]->live);
	if (g_vm->champs[1]->comment != NULL)
	{
		mvwprintw(win[1], 11 + 3 + flag, 4, "%s %s", "Comment :",
				g_vm->champs[1]->comment);
		flag++;
	}
	if (g_vm->champs_nmbr > 1)
	{
		mvwprintw(win[1], 15 + flag, 4, "%s", "Player -2 :");
		mvwprintw(win[1], 16 + flag, 6, "%s %d",
				"Last live :", g_vm->champs[2]->last_live);
		mvwprintw(win[1], 17 + flag, 6, "%s %d",
				"Lives in current period :", g_vm->champs[2]->live);
		if (g_vm->champs[2]->comment != NULL)
		{
			mvwprintw(win[1], 15 + 3 + flag, 4, "%s %s", "Comment :",
					g_vm->champs[2]->comment);
			flag++;
		}
	}
	if (g_vm->champs_nmbr > 2)
	{
		mvwprintw(win[1], 19 + flag, 4, "%s", "Player -3 :");
		mvwprintw(win[1], 20 + flag, 6, "%s %d",
				"Last live :", g_vm->champs[3]->last_live);
		mvwprintw(win[1], 21 + flag, 6, "%s %d",
				"Lives in current period :", g_vm->champs[3]->live);
		if (g_vm->champs[3]->comment != NULL)
		{
			mvwprintw(win[1], 19 + 3 + flag, 4, "%s %s", "Comment :",
					g_vm->champs[3]->comment);
			flag++;
		}
	}
	if (g_vm->champs_nmbr > 3)
	{
		mvwprintw(win[1], 23 + flag, 4, "%s", "Player -4 :");
		mvwprintw(win[1], 24 + flag, 6, "%s %d",
				"Last live :", g_vm->champs[4]->last_live);
		mvwprintw(win[1], 25 + flag, 6, "%s %d",
				"Lives in current period :", g_vm->champs[4]->live);
		if (g_vm->champs[4]->comment != NULL)
		{
			mvwprintw(win[1], 23 + 3 + flag, 4, "%s %s", "Comment :",
					g_vm->champs[4]->comment);
			flag++;
		}
	}
	mvwprintw(win[1], 13 + (4 * (g_vm->champs_nmbr - 1)) +
			8, 6, "%s %d", "CYCLE_TO_DIE :", g_vm->to_die);
	mvwprintw(win[1], 13 + (4 * (g_vm->champs_nmbr - 1)) +
			10, 6, "%s %d", "CYCLE_DELTA :", CYCLE_DELTA);
	mvwprintw(win[1], 13 + (4 * (g_vm->champs_nmbr - 1)) +
			12, 6, "%s %d", "NBR_LIVE :", NBR_LIVE);
	mvwprintw(win[1], 13 + (4 *
		(g_vm->champs_nmbr - 1)) + 14, 6, "%s %d", "MAX_CHECKS :", MAX_CHECKS);
	print_cl_players(win, flag);
}

void		print_window(WINDOW *win[2])
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
	wattron(win[1], COLOR_PAIR(7));
}

void		init(void)
{
	initscr();
	start_color();
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	init_pair(6, COLOR_RED, COLOR_BLACK);
	init_pair(7, COLOR_GREEN, COLOR_BLACK);
	init_pair(8, COLOR_BLUE, COLOR_BLACK);
	init_pair(9, COLOR_CYAN, COLOR_BLACK);
	init_pair(10, 247, COLOR_BLACK);
	init_pair(11, COLOR_WHITE, COLOR_GREEN);
	init_pair(15, 120, COLOR_BLACK);
	init_pair(16, 75, COLOR_BLACK);
	init_pair(17, 162, COLOR_BLACK);
	init_pair(18, 51, COLOR_BLACK);
	init_pair(12, COLOR_WHITE, COLOR_BLUE);
	init_pair(13, COLOR_WHITE, COLOR_RED);
	init_pair(14, COLOR_WHITE, COLOR_CYAN);
}

void		fnkg_shit(WINDOW *win[2], int i)
{
	if (g_vm->map1[i] == 1)
		wattron(win[0], COLOR_PAIR(15));
	else if (g_vm->map1[i] == 2)
		wattron(win[0], COLOR_PAIR(16));
	else if (g_vm->map1[i] == 3)
		wattron(win[0], COLOR_PAIR(17));
	else if (g_vm->map1[i] == 4)
		wattron(win[0], COLOR_PAIR(18));
	else
		wattron(win[0], COLOR_PAIR(5));
	wrefresh(win[1]);
}

void		shit(WINDOW *win[2], int i)
{
	attron(A_BOLD);
	if (g_vm->map1[i] == 1)
	{
		attron(A_BOLD);
		wattron(win[0], COLOR_PAIR(11));
		attron(A_BOLD);
	}
	else if (g_vm->map1[i] == 2)
		wattron(win[0], COLOR_PAIR(12));
	else if (g_vm->map1[i] == 3)
		wattron(win[0], COLOR_PAIR(13));
	else if (g_vm->map1[i] == 4)
		wattron(win[0], COLOR_PAIR(14));
	else
		wattron(win[0], COLOR_PAIR(5));
	wrefresh(win[1]);
}

int			ncurses(int sleep)
{
	WINDOW	*win[2];
	int		y;
	int		x;
	int		z;
	int		i;

	init();
	noecho();
	print_window(win);
	keypad(win[1], TRUE);
	mvwprintw(win[1], 2, 4, "%s   ", "** RUNNING **");
	mvwprintw(win[1], 4, 4, "%s   ", "Cycles/second limit :");
	mvwprintw(win[1], 7, 4, "%s %d", "Cycle :", g_vm->cycle);
	mvwprintw(win[1], 9, 4, "%s %d", "Processes :", g_vm->cars_nmbr);
	print_players(win);
	mvwprintw(win[1], 5, 27, "speed %d         ", sleep);
	y = 1;
	x = 0;
	i = 0;
	z = 1;
	sleep = paused(win, sleep);
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
	return (sleep);
}
