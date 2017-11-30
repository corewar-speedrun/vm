/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_game1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 08:46:04 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/20 09:46:35 by dmaznyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_make_game(t_car *car)
{
	system("say READY? FIGHT!");
	while (g_vm->game > 0)
	{
		vm_make_game3(NULL);
		car = g_vm->cars;
		while (car != NULL)
		{
			if (car->comand == 0)
				vm_read_comand(car);
			if (car->count > 0)
				car->count--;
			car = car->next_car;
		}
		if (g_vm->flag_visualize == 1)
			g_vm->sleep = ncurses(g_vm->sleep);
		vm_make_game2(-1, 0);
	}
}

void	vm_make_game2(int i, int l)
{
	if (g_vm->damp == g_vm->cycle && g_vm->flag_visualize != 1)
	{
		print_maps();
		g_vm->game = 0;
	}
	if (++g_vm->cycle == g_vm->die_cycle)
	{
		vm_car_to_die(NULL, NULL);
		while (++l <= g_vm->champs_nmbr)
			g_vm->champs[l]->live = 0;
	}
	while (++i < MEM_SIZE)
	{
		if (g_vm->map3[i] > 0)
		{
			if (g_vm->map3[i] >= 100)
				g_vm->map3[i] = 0;
			else
				g_vm->map3[i]++;
		}
	}
}

void	vm_make_game3(t_car *car)
{
	car = g_vm->cars;
	while (car != NULL)
	{
		car->f_move = 0;
		if (car->comand == 0 && car->car_next_pos != 0)
			vm_car_next_pos(car);
		if (g_vm->map2[car->car_pos] != 1)
			g_vm->map2[car->car_pos] = 1;
		if (car->count == 0 && car->comand != 0)
			vm_make_move(car);
		if (car->f_move == 0 && car->car_next_pos != 0)
			vm_car_next_pos(car);
		car = car->next_car;
	}
}

/*
** vm_game - главная ф-ция запуска игры.
**
** пока g_vm->game == 1, мы играем. если игра завершена по одной из
** причин, мы меняем флаг и выходим из програмыы, выведя имя победителя на
** экран.
** 
** процессы записаны в листах. ссылка на начало листа в глобальной переменной
** g_vm->cars. с помощью буфера t_car *car, я последовательно каждый процес
** проверяю на:
**
** vm_make_game3
** если команда == 0, и в переменной куда передвинуть каретку есть значение, 
** передвигаю каретку.
** если на карте2 (используется для визуализации положения процессов игры) не
** отмечено, что тм стоит каретка, отмечаем, делая == 1.
** если у нас есть ожидающая выполнения команда и счетчик ожидания дошел до 0,
** пробуем выполнить команду.
** если карента должна буть передвинута, двигаем ее.
**
** vm_make_game
** если команда == 0, значит прроцесс выполнил команду и нужно считать новую,
** или мы на предыдущем ходу стояли на пустой клетке и каретка передвинулась, и
** надо вновь попробовать считать с поля команду.
** если счетчик ожидания ыполнения команды больше нуля, декриментирую его.
** перехожу к следующей каретке(процессу).
**
** vm_make_game2
** первый иф отрабатывает если флаг -damp использован и надо будет на ХХХ цикле
** вывести состояние памяти на экран и завершить игру.
** второй иф отработает, если цикл дошел до момента, когда условие
** смерти кареток наступило и нужно запустить процесс vm_car_to_die.
** последний вайл инкрементирует значения на карте номер 3. она отвечает за
** подсвечивание последних изменений кода на карте.
*/

void	vm_car_to_die(t_car *tmp, t_car *start)
{
	start = g_vm->cars;
	while (start != NULL && start->live < 1)
	{
		tmp = start->next_car;
		g_vm->map2[start->car_pos] = 0;
		free(start);
		g_vm->cars_nmbr -= 1;
		start = tmp;
	}
	g_vm->cars = start;
	if (g_vm->live_checks >= NBR_LIVE || g_vm->max_live_checks <= 0)
	{
		g_vm->to_die -= CYCLE_DELTA;
		g_vm->live_checks = 0;
		g_vm->max_live_checks = MAX_CHECKS;
	}
	else
		g_vm->max_live_checks--;
	g_vm->die_cycle += g_vm->to_die;
	if (g_vm->cars != NULL && g_vm->to_die > 0)
		vm_car_to_die2(NULL, NULL, NULL);
	else
		vm_finish_game();
}

/*
** vm_car_to_die
**
** в первом вайле ищем каретку, которая будет головой списка и на нее будет
** ссылаться g_vm->cars. остальных убираем, декрементируя их количество.
** в последующем if/else мы должны проверить, условие когда нужно уменьшить
** g_vm->to_die на CYCLE_DELTA наступило, или еще нет.
** и если все каретки мертвы, завершаем игру.
*/

void	vm_car_to_die2(t_car *tmp1, t_car *tmp2, t_car *tmp3)
{
	tmp1 = g_vm->cars;
	tmp2 = tmp1->next_car;
	while (tmp2 != NULL)
	{
		tmp3 = tmp2->next_car;
		if (tmp2->live < 1)
		{
			g_vm->map2[tmp2->car_pos] = 0;
			free(tmp2);
			g_vm->cars_nmbr -= 1;
			tmp1->next_car = tmp3;
		}
		else
			tmp1 = tmp1->next_car;
		tmp2 = tmp1->next_car;
	}
	tmp1 = g_vm->cars;
	while (tmp1 != NULL)
	{
		tmp1->live = 0;
		tmp1 = tmp1->next_car;
	}
}

/*
** vm_car_to_die2
**
** в первом вайле проходим, фришим остальные каретки, которые нужно убить.
** во втором вайле обнуляем  переменную лайв, на которую при очистке игры от
** мертвых кареток и ориентиремся.
*/
