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
#include "libft/libft.h"
#include "op.h"

typedef struct		s_vm
{
	int				error;
	int				champs;
	unsigned char	buf;
}					t_vm;

typedef struct		s_champ
{
	char			*name;
	char			*comment;
	unsigned char	*src;
	int				nmbr;
}					t_champ;

union	u_read
{
	unsigned char bit[4];
	unsigned int  mg;
};

int		main(int argv, char **argc);
t_vm	*vm_init(void);
void	vm_read(t_vm *vm, int argv, char **argc);
int		vm_magic(t_vm *vm, int fd);
void	vm_parsing(t_vm *vm, int fd);
int		vm_error(int error);
void	vm_read_flag(t_vm *vm, char *str);
int		vm_usage(char *re);