/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 13:22:03 by dverbyts          #+#    #+#             */
/*   Updated: 2017/10/31 13:22:06 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

union				u_read
{
	unsigned char	bit[4];
	unsigned int	mg;
};

/*
** u_read - вспомогательная структура для парсинга
*/

/*
** vm_read_flag - работа с флагами. Закодить.////////////////////////////////////////////
*/

void			vm_read_flag(t_vm *vm, char *str)
{
	if (vm)
		return ;
	if (str)
		return ;
	return ;
}

void			vm_read(t_vm *vm, int i, char **arg)
{
	int			fd;
	int			x;

	x = 0;
	while (++x < i)
	{
		if((fd = open(arg[x], O_RDONLY)) == -1 && vm->error == -1)
			vm->error = 2;
		if (arg[x][0] == '-' && vm->error == -1)
			vm_read_flag(vm, arg[x]);
		else if (vm_read_magic(vm, fd) == 1 && vm->error == -1)
			vm->champs[vm->champs_nmbr++] = vm_parsing(vm, fd);
		else
			vm->error = 1;
		if (vm->error != -1)
			break ;
	}
	if (vm->champs_nmbr < 1 && vm->error != -1)
		vm->error = 7;
}

/*
** vm_read - главная ф-ция чтения
**
** int i - количество аргументов, которые нам дали. 
** char **arg - массив аргументовю.
** 
** Открываю файл, получая его fd. 
** Если arg[i][0] == '-', значит это флаг и парсим его как флаг.
** В ином случае это либо чемпион, либо мусор. Проверить можно сверив MAGIC.
** vm_read_magic - проверяет первые 4 байта на соответствие COREWAR_EXEC_MAGIC.
** Если vm_read_magic вернуло 1, это чемпион, начинаем его парсить. Если 
** вернуло 0, нам засунули дичь, посылаем нафиг, выводим usage.
*/

t_champ				*vm_parsing(t_vm *vm, int fd)
{
	t_champ			*tmp;
	unsigned char	buf[10];

	if (!(tmp = (t_champ *)malloc(sizeof(t_champ) * 1)))
		return (NULL);
	ft_bzero(tmp, sizeof(t_champ));
	if (vm->error == -1)
		tmp->name = (char *)vm_read_script(vm, PROG_NAME_LENGTH + 4, fd, 1);
	if (vm->error == -1)
		tmp->size = vm_read_size(vm, 4, fd);
	if (vm->error == -1)
		tmp->comment = (char *)vm_read_script(vm, COMMENT_LENGTH + 4, fd, 1);
	if (vm->error == -1 && tmp->size <= (MEM_SIZE / 6))
		tmp->src = vm_read_script(vm, tmp->size, fd, 0);
	else if (vm->error == -1)
		vm->error = 4;
	if (read(fd, &buf, 10) != 0)
		vm->error = 6;
	return (tmp);
}

/*
** vm_parsing - малочим память под чемпиона и парсим в нее чемпиона
**
** tmp->name - имя чемпиона. кащу к char.
** tmp->size - размер рабочего кода чемпиона. считываю согласно этого размера и
** на поле размещать исходя из этого значения. перевожу в инт через атои_бейс.
** tmp->comment - комент. в оригинальной ВМ без визуализатора выводится, с 
** визуализатором не используется. у нас должно выводится dвезде. кащу в char.
** tmp->src - исходный код чемпиона. размещается на игровом поле.
*/

int					vm_read_size(t_vm *vm, int i, int fd)
{
	int				z;
	int				x;
	unsigned char	buf[i];

	z = 0;
	x = -1;
	if (read(fd, &buf, i) != i)
		vm->error = 2;
	if (vm->error == -1)
	{
		while (++x < i)
			z = z << 8 | buf[x];
	}
	return (z);
}

/*
** vm_read_int - парсим размер программы в int
**
** из unsigned char побитовыми манипуляциями кастим нах размер.
** каст происходит задом наперед.
*/

unsigned char		*vm_read_script(t_vm *vm, int i, int fd, int flag)
{
	unsigned char	buf[i];
	unsigned char	*mem;
	int				s;

	s = -1;
	if (read(fd, &buf, i) != i)
		vm->error = 2;
	if (flag == 1 && vm->error == -1 && (buf[i - 1] != 0 || buf[i - 2] != 0 ||
		buf[i - 3] != 0 || buf[i - 4] != 0))
		vm->error = 5;
	if (flag == 1 && vm->error == -1)
		return ((unsigned char *)ft_strdup((char *)buf));
	else if (vm->error == -1)
	{
		if (!(mem = (unsigned char *)malloc(sizeof(unsigned char) * i + 1)))
			return (NULL);
		while (++s < i)
			mem[s] = buf[s];
		mem[s] = 0;
		return (mem);
	}
	return (NULL);
}

/*
** vm_read_script - считываю чемпиона кусок за куском.
**
** flag:
** 1 - надо последние 4 байта проверить, чтобы были == 0 && эти данные можно 
** просто закастить в char.
** 0 - ничего проверять не надо, просто читываем С КОНЦА.
*/

int					vm_read_magic(t_vm *vm, int fd)
{
	union u_read	smpl;
	unsigned char	r[4];

	smpl.mg = COREWAR_EXEC_MAGIC;
	if (read(fd, &r, 4) != 4)
		vm->error = 2;
	if (vm->error == -1 && (r[0] == smpl.bit[3] || r[0] == smpl.bit[0]) &&
		(r[1] == smpl.bit[2] || r[1] == smpl.bit[1]) &&
		(r[2] == smpl.bit[1] || r[2] == smpl.bit[2]) &&
		(r[3] == smpl.bit[0] || r[3] == smpl.bit[3]))
		return (1);
	else if (vm->error == -1)
		vm->error = 3;
	return (0);
}

/*
** 4 байта - меджик число
** 132 байта - имя
** 4 байта - значение размера программы
** 2052 байта - коммент
** (значение из f3) байт - размер программы
*/
