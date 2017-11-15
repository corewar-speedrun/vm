/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ireva <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 17:55:08 by ireva             #+#    #+#             */
/*   Updated: 2017/10/31 14:49:29 by ireva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <mach/mach_types.h>
#include "corewar.h"


int	paused(WINDOW *win[2], int sleep) {
	int ch;
	int i;

	ch = wgetch(win[1]); //отслеживает паузу
	if (ch == ' ') {
		mvwprintw(win[1], 2, 4, "%s   ", "** PAUSED **");
		wrefresh(win[1]);
		i = 1;
		while (i == 1) {
			ch = wgetch(win[1]);
			if (ch == ' ') {
				mvwprintw(win[1], 2, 4, "%s   ", "** RUNNING **");
				wrefresh(win[1]);
				i--;
			}
		}

	}
    if (ch == KEY_DOWN && sleep != 0)
        sleep -= 2500;
    if (sleep <= 0)
        sleep = 1;
    if (ch == KEY_UP && sleep != 0)
        sleep += 2500 ;
	if (ch == 'q')
		exit(0);
    return (sleep);
}

void    players_color(WINDOW *win[2], int i)
{
    //Назначает цвет каждому плееру
     if (g_vm->map[1][i] == 1)
        wattron(win[0], COLOR_PAIR(7));
    else if (g_vm->map[1][i] == 2)
        wattron(win[0], COLOR_PAIR(8));
    else if (g_vm->map[1][i] == 3)
        wattron(win[0], COLOR_PAIR(6));
    else if (g_vm->map[1][i] == 4)
        wattron(win[0], COLOR_PAIR(9));
     else
         wattron(win[0], COLOR_PAIR(10));
    wrefresh(win[1]);
}

void    print_cl_players(WINDOW *win[2])
{
    wattron(win[1], COLOR_PAIR(7));
    mvwprintw(win[1], 11, 16, "%s",  g_vm->champs[1]->name);
    if (g_vm->champs_nmbr > 1)
    {
        wattron(win[1], COLOR_PAIR(8));
        mvwprintw(win[1], 15, 16, "%s", g_vm->champs[2]->name);
    }
    if (g_vm->champs_nmbr > 2)
    {
        wattron(win[1], COLOR_PAIR(6));
        mvwprintw(win[1], 19 , 16, "%s", g_vm->champs[3]->name);
    }
    if (g_vm->champs_nmbr > 3)
    {
        wattron(win[1], COLOR_PAIR(9));
        mvwprintw(win[1], 23, 16, "%s", g_vm->champs[4]->name);
    }
    wattroff(win[1], COLOR_PAIR(9));
    wrefresh(win[1]);   
}

void	print_players(WINDOW *win[2])
{
//	int num_of_players;
//Пришет кол-во игроков и  прочее"
    mvwprintw(win[1], 11, 4, "%s", "Player -1 :");
    mvwprintw(win[1], 12, 6, "%s   ", "Last live :");
    mvwprintw(win[1], 13, 6, "%s   ", "Lives in current period :");
    if (g_vm->champs_nmbr > 1) {
        mvwprintw(win[1], 15, 4, "%s", "Player -2 :");
        mvwprintw(win[1], 16, 6, "%s   ", "Last live :");
        mvwprintw(win[1], 17, 6, "%s   ", "Lives in current period :");
    }
    if (g_vm->champs_nmbr > 2) {
        mvwprintw(win[1], 19, 4, "%s", "Player -3 :");
        mvwprintw(win[1], 20, 6, "%s   ", "Last live :");
        mvwprintw(win[1], 21, 6, "%s   ", "Lives in current period :");
    }
    if (g_vm->champs_nmbr > 3) {
        mvwprintw(win[1], 23, 4, "%s", "Player -4 :");
        mvwprintw(win[1], 24, 6, "%s   ", "Last live :");
        mvwprintw(win[1], 25, 6, "%s   ", "Lives in current period :");
    }
    mvwprintw(win[1], 13 + (4 * (g_vm->champs_nmbr - 1)) + 8, 6, "%s %d", "CYCLE_TO_DIE :", g_vm->to_die);
    mvwprintw(win[1], 13 + (4 * (g_vm->champs_nmbr - 1)) + 10, 6, "%s %d", "CYCLE_DELTA :", CYCLE_DELTA);
    mvwprintw(win[1], 13 + (4 * (g_vm->champs_nmbr - 1)) + 12, 6, "%s %d", "NBR_LIVE :", NBR_LIVE);
    mvwprintw(win[1], 13 + (4 * (g_vm->champs_nmbr - 1)) + 14, 6, "%s %d", "MAX_CHECKS :", MAX_CHECKS);
    print_cl_players(win);
}


void	print_window(WINDOW *win[2])
{
	win[0] = newwin(68, 196, 0, 0); //окно для поля
	win[1] = newwin(68, 70, 0, 195);// окно для статы
	nodelay(win[1], TRUE); 
	nodelay(win[0], TRUE); 
	//keypad(draw->win[0], TRUE);
	wattron(win[0], COLOR_PAIR(5)); // каждый раз когда хотим менять цвет указываем номер пары цветов (строка 9), перед выводом
	wborder(win[0], '*', '*', '*', '*', '*', '*', '*', '*');  // рамка
	wattron(win[1], COLOR_PAIR(5)); 
	wborder(win[1], '*', '*', '*', '*', '*', '*', '*', '*');
	wattron(win[0], COLOR_PAIR(6)); 
	wattron(win[1], COLOR_PAIR(7));
}

void	init()
{
	initscr(); //инициализация окна 
	start_color();//для того чтобы цвета запускались
	init_pair(5, COLOR_BLACK, COLOR_WHITE); // объявляем цвет белый фон, черный шрифт
	init_pair(6, COLOR_RED, COLOR_BLACK); 
	init_pair(7, COLOR_GREEN, COLOR_BLACK);
    init_pair(8, COLOR_BLUE, COLOR_BLACK);
    init_pair(9, COLOR_CYAN, COLOR_BLACK);
    init_pair(10, 247, COLOR_BLACK);

}

//КОМПИЛИТЬ С ФЛАГОМ -lncurses   !!!!
int ncurses(int kakoito_int, int sleep)
{
	WINDOW *win[2];
	int y;
	int x;
	int z;
	int i;

	init();
	noecho();// потом будет полезно
	print_window(win);
	keypad(win[1], TRUE);
	mvwprintw(win[1], 2, 4, "%s   ", "** RUNNING **");
	mvwprintw(win[1], 4, 4, "%s   ", "Cycles/second limit :");
	mvwprintw(win[1], 7, 4, "%s %d", "Cycle :", kakoito_int);
	mvwprintw(win[1], 9, 4, "%s %d", "Processes :",  g_vm->cars_nmbr);
    print_players(win);
    mvwprintw(win[1], 5, 27,  "speed %d         ",  sleep);
	y = 1;
	x = 0;
    i = 0;
    z  = 1;
	//переместить курсор
	wmove(win[0],y,x);
	//цикл который рисует память
    sleep = paused(win, sleep);
    //speed(win);
	while (++y < 66) {
        x = 2;
        while (x < 194) {
            players_color(win, i);
            mvwprintw(win[0], y, x, "%.2x", g_vm->map[0][i]);
            x += 3;
           // players_color(win, i);
            i++;
        }
        usleep((useconds_t) sleep);
    }
	wrefresh(win[0]); //перерисовывать
	wrefresh(win[1]);
//    players_color(win, 2, kakoito_int);
//	while (1)
//	{}
  //  usleep((useconds_t) sleep);
	return (sleep);
}

//int	main()
//{
//	int i;
//	int j;
//    int sleep;
//
//	i = 0;
//	j = 0;
//    sleep = 10000;
//	while (i < 2147483646)
//	{
//		sleep = ncurses(j, sleep);
//		j++;
//		i++;
//	}
//}
