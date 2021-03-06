/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 01:53:37 by lcharvol          #+#    #+#             */
/*   Updated: 2017/03/24 01:53:38 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			print_res_visu(t_core *core, t_env *p)
{
	t_player	*player;
	t_player	*winner;

	player = core->player;
	winner = core->player;
	p->melenchon = 1;
	while (player)
	{
		if (player->last_live > winner->last_live)
			winner = player;
		player = player->next;
	}
	p->winnername = winner->name;
	print_winner(winner);
}

void			ft_draw_arena(t_env *p)
{
	ft_modif_color(15, 15, 15, p);
	ft_draw_square(10, 10, (HEIGHT - 20), p);
	ft_draw_map(p);
}

void			ft_draw_menu(t_env *p)
{
	ft_modif_color(35, 35, 35, p);
	p->h = 200;
	p->l = WIDTH - (HEIGHT + 10);
	ft_draw_rectangle((HEIGHT), 10, p);
	p->h = (HEIGHT) - 230;
	p->l = WIDTH - (HEIGHT + 10);
	ft_draw_rectangle((HEIGHT), 220, p);
	ft_modif_color(30, 30, 30, p);
	p->h = 235;
	p->l = WIDTH - (HEIGHT + 50);
	ft_draw_rectangle((HEIGHT) + 20, 240, p);
	ft_modif_color(30, 30, 30, p);
	p->h = 600;
	p->l = WIDTH - (HEIGHT + 50);
	ft_draw_rectangle((HEIGHT) + 20, 490, p);
}

void			ft_draw_background(t_env *p)
{
	int			i;

	i = 0;
	while (i < (HEIGHT * WIDTH * 4))
	{
		(p->ret)[i] = 20;
		(p->ret)[i + 1] = 20;
		(p->ret)[i + 2] = 20;
		(p->ret)[i + 3] = 0;
		i += 4;
	}
}
