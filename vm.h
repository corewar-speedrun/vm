/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:46:15 by dverbyts          #+#    #+#             */
/*   Updated: 2017/10/24 14:46:17 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>/////////////////////////////////////////////////////////
#include "libft/libft.h"
#include "op.h"

typedef struct		s_champ
{
	char			*name;
	char			*comment;
	unsigned char	*src;
	int				size;
	int				nmbr;
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

typedef struct		s_vm
{
	int				error;
	int				champs_nmbr;
	t_champ			**champs;
	unsigned char	*map;
}					t_vm;

/*
** t_vm - главная структура виртуальной машины.
**
** error - изначально равен -1. если у переменной другое значение, это
** говорит о необходимости остановить работы программы и вывести
** соответствующее сообщение об ошибке.
** champs_nmbr - количество чемпионов, которое нам зашло
** champs - масив с указателями на структуры t_champ
** map - игровое поле unsigned char длиной MEM_SIZE, на котором изначально
** размещаем чемпионов и играем.
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
t_vm				*vm_init(void);
t_champ				*vm_parsing(t_vm *vm, int fd);
void				vm_read(t_vm *vm, int argv, char **argc);
unsigned char		*vm_read_script(t_vm *vm, int i, int fd, int flag);
int					vm_read_magic(t_vm *vm, int fd);
void				vm_read_flag(t_vm *vm, char *str);
int					vm_read_size(t_vm *vm, int i, int fd, int flag);

/*
** VM_init_game_&&_plase_champs
*/

void				vm_make_game(t_vm *vm);
unsigned char		*vm_init_game(t_vm *vm);

/*
** VM_error_management
*/

int					vm_error(int error);
int					vm_usage(char *re);

/*
** VM_help_scripts
*/

//char				*vm_strjoin(char *t, char *y);
