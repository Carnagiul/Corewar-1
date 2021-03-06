/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_n_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 08:19:44 by abarriel          #+#    #+#             */
/*   Updated: 2017/04/20 22:27:41 by cseccia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned char	apply_mask(unsigned char cde, int arg)
{
	if (arg == 1)
		return ((cde & 192) >> 6);
	if (arg == 2)
		return ((cde & 48) >> 4);
	if (arg == 3)
		return ((cde & 12) >> 2);
	return (cde);
}

unsigned int	return_arg(t_core *core, t_process *process, int index, int cde)
{
	unsigned int	res;

	if (cde == REG_CODE)
	{
		res = 0;
		res |= core->mem[index % MEM_SIZE];
		res = chatoi(process->reg[res - 1]);
		return (res);
	}
	if (cde == IND_CODE && core->tmp_id != 2)
	{
		res = (unsigned short int)chatohi(&(core->mem[index % MEM_SIZE]));
		res = chatoi(&(core->mem[uns_int((process->pc + res) % MEM_SIZE)]));
		if (core->tmp_id != 1)
			res %= IDX_MOD;
	}
	if (cde == DIR_CODE || core->tmp_id == 2)
	{
		if (!process->op->l_size && cde == DIR_CODE)
			res = chatoi(&(core->mem[index % MEM_SIZE]));
		else
			res = chatohi(&(core->mem[index % MEM_SIZE]));
	}
	return (res);
}

unsigned char	return_good_value(unsigned char cde, t_process *process)
{
	if (cde == REG_CODE)
		return (1);
	if (cde == IND_CODE)
		return (2);
	if (cde == DIR_CODE)
	{
		if (!process->op->l_size)
			return (4);
		return (2);
	}
	return (0);
}

unsigned int	get_n_arg(t_core *core, t_process *process, int arg, int md)
{
	unsigned char	cde;
	unsigned char	i;
	int				index;

	core->tmp_id = md;
	cde = apply_mask(core->mem[(process->pc + 1) % MEM_SIZE], arg);
	if (arg == 1)
		return (return_arg(core, process, (process->pc + 2) % MEM_SIZE, cde));
	if (arg == 2)
	{
		i = return_good_value((((core->mem[(process->pc + 1) % MEM_SIZE])
		& 192) >> 6), process);
		index = ((process->pc + 2) + i) % MEM_SIZE;
		return (return_arg(core, process, index, cde));
	}
	if (arg == 3)
	{
		i = return_good_value((((core->mem[(process->pc + 1) % MEM_SIZE])
		& 192) >> 6), process);
		i += return_good_value((((core->mem[(process->pc + 1) % MEM_SIZE])
		& 48) >> 4), process);
		index = ((process->pc + 2) + i) % MEM_SIZE;
		return (return_arg(core, process, index, cde));
	}
	return (0);
}
