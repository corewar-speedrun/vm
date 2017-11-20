/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ireva <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 17:01:25 by ireva             #+#    #+#             */
/*   Updated: 2017/11/20 17:09:48 by ireva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		with_comment(WINDOW *win[2])
{
	wattron(win[1], COLOR_PAIR(7));
	mvwprintw(win[1], 11, 16, "%s", g_vm->champs[1]->name);
	if (g_vm->champs_nmbr > 1 && g_vm->flag > 0)
	{
		wattron(win[1], COLOR_PAIR(8));
		mvwprintw(win[1], 15 + 1, 16, "%s", g_vm->champs[2]->name);
		g_vm->flag--;
	}
	if (g_vm->champs_nmbr > 2 && g_vm->flag > 0)
	{
		wattron(win[1], COLOR_PAIR(6));
		mvwprintw(win[1], 19 + 2, 16, "%s", g_vm->champs[3]->name);
		g_vm->flag--;
	}
	if (g_vm->champs_nmbr > 3 && g_vm->flag > 0)
	{
		wattron(win[1], COLOR_PAIR(9));
		mvwprintw(win[1], 23 + 3, 16, "%s", g_vm->champs[4]->name);
	}
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
	sleep = key_managment(ch, sleep);
	return (sleep);
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
	init_pair(19, COLOR_WHITE, COLOR_BLACK);
}
