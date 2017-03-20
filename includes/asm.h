/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 06:07:00 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/20 01:13:45 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft.h"

typedef struct	s_asm
{
	char		*champ_name;
	int			fd_champ;
	int			fd_cor;
	char		*cor;
}				t_asm;
t_asm			*init_asm(void);
#endif
