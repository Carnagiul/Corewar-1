/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 08:53:16 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/27 08:53:17 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		create_file(t_asm *a, t_lab *l, t_header *h)
{
	if (!l)
	{
		ft_dprintf(2, "No instructions found for %s\n", h->prog_name);
		exit(1);
	}
	if ((a->fd_cor = open(a->cor, O_CREAT | O_WRONLY |
		O_APPEND | O_TRUNC, 0644)) < 0)
		ft_exit("Cannot create file");
}

static void		f_write_cmd(t_asm *a, t_cmd *c, t_op op_t)
{
	short	index;

	index = 0;
	while (index != op_t.nbr_args)
	{
		if (c->typs[index] & T_REG)
			write(a->fd_cor, &(c->r[index]), sizeof(c->r[index]));
		if (c->typs[index] & T_DIR)
		{
			if (!op_t.idk1)
				write(a->fd_cor, &(c->d4[index]), sizeof(c->d4[index]));
			else
				write(a->fd_cor, &(c->d2[index]), sizeof(c->d2[index]));
		}
		if (c->typs[index] & T_IND)
			write(a->fd_cor, &(c->ind[index]), sizeof(c->ind[index]));
		index++;
	}
}

static void		final_write_(t_asm *a, t_cmd *cmd)
{
	while (cmd)
	{
		write(a->fd_cor, &(cmd->code), sizeof(cmd->code));
		if (g_op[cmd->nb_struct].idk == 1)
			write(a->fd_cor, &(cmd->barg), sizeof(cmd->barg));
		f_write_cmd(a, cmd, g_op[cmd->nb_struct]);
		cmd = cmd->next;
	}
}

void			final_write(t_asm *a, t_header *h, t_lab *l, char *name)
{
	short i;

	i = -1;
	create_file(a, l, h);
	write(a->fd_cor, h, sizeof(t_header));
	while (l)
	{
		final_write_(a, l->cmd);
		l = l->next;
	}
	close(a->fd_cor);
	ft_putstr("Writing output program to ");
	ft_putstr(RED);
	while (++i < (short)(ft_strlen(name) - 2))
		ft_putchar(name[i]);
	ft_putstr(".cor\n");
	ft_putstr(RESET);
}
