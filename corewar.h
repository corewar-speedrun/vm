/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:46:15 by dverbyts          #+#    #+#             */
/*   Updated: 2017/10/24 14:46:17 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <unistd.h>
# include <stdio.h>////////////////////////////////////////////////////////////////
# include "libft/libft.h"
# include "op.h"

# define TRUE 1 
# define FALSE 0 

typedef struct		s_champ
{
	char			*name;
	char			*comment;
	unsigned char	*src;
	int				size;
	int				nmbr;
	int				live;
	int				last_live;
}					t_champ;

/*
** t_champ - структура с одним чемпионом и всей инфой по нему.
**
** name - имя
** comment - комент
** src - код чемпиона, который помещаем на игровое поле
** size - длина src байт
** nmbr - номер чемпиона по порядку
*/

typedef struct		s_car
{
	int				car_pos;
	int				car_next_pos;
	int				count;
	int				comand;
//	int				cost;
	int				car_reg[16];
	int				carry;
	int				live;
	struct s_car	*next_car;
}					t_car;

/*
** t_car - каретка / процесс
** 
** car_pos - положение на карте
** count - счетчик циклов до выполнения команды
** cost - стоимость(количество) циклов для выполнения команды // возможно достаточно будет count
** car_reg - регистр.
** ** 0 регистр - номер чемпиона, вызвавшего данный процесс со знаком минус (-1 или -3 и т.д.)  
** next_car - следуюзая каретка / процесс
*/

typedef struct		s_vm
{
	int				game;
	int				error;
	int				champs_nmbr;
	t_champ			**champs;
	unsigned char	**map;
	t_car			*cars;
	int				damp;
	int				cycle;
	int				die_cycle;
	int				to_die;
}					t_vm;

t_vm				*g_vm;

/*
** t_vm - главная структура виртуальной машины.
**
** game - (== 1 играем) (== 2 стоим на паузе) (== 0 прекратили игру)
** error - изначально равен -1. если у переменной другое значение, это
** ** говорит о необходимости остановить работу программы и вывести
** ** соответствующее сообщение об ошибке.
** champs_nmbr - количество чемпионов, которое нам зашло
** champs - масив с указателями на структуры t_champ
** map - игровое поле unsigned char длиной MEM_SIZE
** ** map[0] - карта выводится на экран, код чемпионов и все изменения на ней
** ** map[1] - клетка != 0 означает, что точка на карте принадлежит боту.
** ** ** значение клетки == номеру бота.
** ** map[2] - если клетка == 1, на ней размещена каретка.
** ** map[3] - если клетка == 1, за последние Х циклов тут изменился код (решить чему рвен Х)
** cars - список цсех кареток / процессов
** damp - при применении флага damp, останавливает игру на указанном цикле и выводит результат на экран. //// еще не реализованно
** cycle - номер текущего игрового цикла
** to_die - через сколько циклов с последней чистки трупов кареток произойдет следующая
** die_cycle - цикл на котором произойдет очередная смерть кареток не подавших
** ** признаков жизнию
*/

union				u_read
{
	unsigned char	bit[4];
	unsigned int	mg;
};

/*
** u_read - вспомогательная структура для парсинга
*/

/*
** VM_parsing
*/

int					main(int argv, char **argc);
void				vm_init(void);
t_champ				*vm_parsing(int fd);
void				vm_read(int argv, char **argc);
unsigned char		*vm_read_script(int i, int fd, int flag);
int					vm_read_magic(int fd);
void				vm_read_flag(char *str);
int					vm_read_size(int i, int fd);

/*
** VM_init_game_&&_plase_champs
*/

void				vm_init_champs(void);
void				vm_init_car(int pos, int champ_nmbr, t_car *origin);

/*
** VM_game
*/

void				vm_make_game(t_car *car);
void				vm_make_game2(t_car *car);
void				vm_car_to_die(void);
void				vm_car_to_die2(void);
t_car				*vm_read_comand(t_car *car);
t_car				*vm_make_move(t_car *car);
t_car				*vm_make_move2(t_car *car);
t_car				*vm_car_next_pos(t_car *car);

/*
** VM_comands
*/

t_car				*vm_com_live(t_car *car);
t_car				*vm_com_ld(t_car *car);
t_car				*vm_com_st(t_car *car);
t_car				*vm_com_add(t_car *car);
t_car				*vm_com_sub(t_car *car);
t_car				*vm_com_and(t_car *car);
t_car				*vm_com_or(t_car *car);
t_car				*vm_com_xor(t_car *car);
t_car				*vm_com_zjmp(t_car *car);
t_car				*vm_com_ldi(t_car *car);
t_car				*vm_com_sti(t_car *car);
t_car				*vm_com_fork(t_car *car);
t_car				*vm_com_lld(t_car *car);
t_car				*vm_com_lldi(t_car *car);
t_car				*vm_com_ifork(t_car *car);
t_car				*vm_com_aff(t_car *car);

/*
** VM_error_management
*/

int					vm_error(int error);
int					vm_usage(char *re);

/*
** VM_help_scripts
*/

//char				*vm_strjoin(char *t, char *y);
void				print_maps(void);
int					vm_cycles_count(int tmp);

#endif
