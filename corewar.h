/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:46:15 by dverbyts          #+#    #+#             */
/*   Updated: 2017/11/20 18:34:42 by dmaznyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "ncurses.h"

# define MAX_PLAYERS		4
# define MEM_SIZE			(4*1024)
# define IDX_MOD			(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

# define REG_NUMBER			16
# define REG_SIZE			4

# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC	0xea83f3

# define TRUE		1
# define FALSE		0

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
** live - сколько раз боту засчиталась команда live
** last_live - номер последнего цикла, на котором боту засчиталась команда live
*/

typedef struct		s_car
{
	int				nabr;
	int				car_pos;
	int				car_next_pos;
	int				count;
	int				comand;
	int				com_args[3];
	unsigned char	c_byte[3];
	int				car_reg[REG_NUMBER + 1];
	int				carry;
	int				live;
	int				f_move;
	struct s_car	*next_car;
	struct s_champ	*champ;
}					t_car;

/*
** t_car - каретка / процесс
**
** car_pos - положение на карте
** car_next_pos - следующее положение (куда должна передвинуться картека)
** count - счетчик циклов до выполнения команды
** comand - команда, которая сейчас выполняетс, ее номер
** com_args - регистр оргументов, которые считываются в процессе выполнения
** ** команды с поля или другого места
** c_byte - расшифрованные кодирующие байты для каждого артумента
** car_reg - регистр.
** ** 0 регистр - служебный. для парсинга
** ** 1 регистр - номер чемпиона, вызвавшего данный процесс
** ** со знаком минус (-1 или -3 и т.д.)
** carry - флаг для команды джамп. если carry == 1 - джамп сработает.
** live - показатель живая каретка или нет. если == 0, при следующем поиске
** ** кареток подлежащих смерти, эта сдохнет.
** f_move - флаг. если == 1, каретка уже меняла свою позицию в этом цикле.
** ** нужно для коректной работы логики перемещения кареток.
** next_car - следуюзая каретка / процесс
** champ - ссылка на чемпиона, которому каретка пинадлежит
*/

typedef struct		s_vm
{
	int				game;
	int				error;
	int				champs_nmbr;
	int				cars_nmbr;
	t_champ			**champs;
	unsigned char	*map0;
	unsigned char	*map1;
	unsigned char	*map2;
	unsigned char	*map3;
	t_car			*cars;
	int				damp;
	int				cycle;
	int				die_cycle;
	int				live_checks;
	int				max_live_checks;
	int				to_die;
	int				flag_say_alive;
	int				flag_visualize;
	int				sleep;
	int				flag;
	int				move;
	int				nambering[5];
	int				namber;
	unsigned char	r[4];
}					t_vm;

extern t_vm			*g_vm;

/*
** t_vm - главная структура виртуальной машины.
**
** game - (== 1 играем) (== 2 стоим на паузе) (== 0 прекратили игру)
** error - изначально равен -1. если у переменной другое значение, это
** ** говорит о необходимости остановить работу программы и вывести
** ** соответствующее сообщение об ошибке.
** champs_nmbr - количество чемпионов, которое нам зашло
** cars_nmbr - счетчик количества процессов.
** champs - масив с указателями на структуры t_champ
** map - игровое поле unsigned char длиной MEM_SIZE
** ** map[0] - карта выводится на экран, код чемпионов и все изменения на ней
** ** map[1] - клетка != 0 означает, что точка на карте принадлежит боту.
** ** ** значение клетки == номеру бота.
** ** map[2] - если клетка == 1, на ней размещена каретка.
** ** map[3] - если клетка > 0, за последние Х циклов тут
** ** ** изменился код (решить чему равен Х)
** cars - список цсех кареток / процессов
** damp - при применении флага damp, останавливает игру на указанном цикле
** и выводит результат на экран. //// еще не реализованно
** cycle - номер текущего игрового цикла
** live_checks и max_live_checks - флаги для правильной работы логики
** ** жизни и смерти кареток.
** to_die - через сколько циклов с последней чистки трупов кареток
** произойдет следующая
** die_cycle - цикл на котором произойдет очередная смерть кареток не подавших
** ** признаков жизнию
** flag_say_alive - флаг для команды выводящей все крики лайв. работает толко
** ** без визуализации.
** flag_visualize - если == 1, включаем с визуализацией при помощи энкерсис
** sleep - скорость отработки с визуализацией
** flag и move - какие-то флаги для визуализации.
** nambering - хранилище для номера бота, задаваемого при флаге ``-n число``
** namber - номер в какую ячейку nambering писать флаг.
** r - переменная, необходимая для чтения и валидации мэджик числа у бота.
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
void				vm_init(int i);
t_champ				*vm_parsing(int fd);
unsigned char		*vm_read_script(int i, int fd, int flag);
int					vm_read_magic(int fd, int flag);
int					vm_read_flag(char *str);
int					vm_read_flag2(int i, char **arg, int x, int flag);
int					vm_read_flag3(int i, char **arg, int x, int flag);
int					vm_read_flag4(char **arg, int x);
int					vm_read_size(int i, int fd);
void				vm_read1(int i, char **arg, int x, int flag);
void				vm_split_champs(void);

/*
** VM_init_game_&&_plase_champs
*/

void				vm_init_champs(void);
void				vm_init_car(int pos, int next, int champ_nmbr, t_car *car);

/*
** VM_game_algoritm
*/

void				vm_make_game(t_car *car);
void				vm_make_game2(int i, int l);
void				vm_make_game3(t_car *car);
void				vm_car_to_die(t_car *tmp, t_car *start);
void				vm_car_to_die2(t_car *tmp1, t_car *tmp2, t_car *tmp3);
void				vm_read_comand(t_car *car);
void				vm_make_move(t_car *car);
void				vm_make_move2(t_car *car);
void				vm_car_next_pos(t_car *car);
int					vm_find_next_pos2(t_car *car, int r, int c_nmbr, int i);
int					vm_cycles_count(int tmp);
void				vm_finish_game(void);
void				vm_map_write(int c, int p, t_car *car);
int					vm_cycles_count(int tmp);
void				print_maps(void);

/*
** VM_comandss
*/

void				vm_com_live(t_car *car);
void				vm_com_live2(int champ_namber);
void				vm_com_ld(t_car *car);
void				vm_com_st(t_car *car);
void				vm_com_add(t_car *car);
void				vm_com_sub(t_car *car);
void				vm_com_and(t_car *car);
void				vm_com_or(t_car *car);
void				vm_com_xor(t_car *car);
void				vm_com_zjmp(t_car *car);
void				vm_com_ldi(t_car *car);
void				vm_com_ldi2(t_car *car);
void				vm_com_sti(t_car *car);
void				vm_com_sti2(t_car *car, int tmp, int tmp2, int tmp3);
void				vm_com_fork(t_car *car);
void				vm_com_lld(t_car *car);
void				vm_com_lldi(t_car *car);
void				vm_com_lldi2(t_car *car);
void				vm_com_ifork(t_car *car);
void				vm_com_aff(t_car *car);
void				vm_parse_code_byte(t_car *car);
int					vm_find_next_pos(t_car *car);
void				vm_car_clean(t_car *car);
void				vm_parse_code_byte(t_car *car);
void				vm_get_reg_dir(t_car *car, int index, int i);
void				vm_get_ind(t_car *car, int index, int i);
int					vm_get_arg(t_car *car, int arg, int i);
int					vm_get_t_reg(t_car *car, int index, int i);
int					vm_get_t_dir(t_car *car, int index, int i);
int					vm_get_t_ind(t_car *car, int index, int i);

/*
** VM_error_management
*/

int					vm_error(int error);
int					vm_usage(char *re);

/*
** VM_vizualization
*/

int					ncurses(int sleep);
void				with_comment(WINDOW *win[2]);
void				shit(WINDOW *win[2], int i);
void				fnkg_shit(WINDOW *win[2], int i);
int					paused(WINDOW *win[2], int sleep);
void				init(void);
void				print_f_player(WINDOW *win[2]);
void				print_s_player(WINDOW *win[2]);
void				print_th_player(WINDOW *win[2]);
void				print_fo_player(WINDOW *win[2]);
void				players_color(WINDOW *win[2], int i);
int					key_managment(int ch, int sleep);

#endif
