/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 01:44:25 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/21 12:56:22 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "locale.h"
void 	header_name(char *line, t_header *h, t_asm *a)
{
	skip_space(&line);
	if (*line != '"' && !ft_strchr(LABEL_CHARS, *line))
		return (lexical_error(a->count_line, a->len_line - ft_strlen(line)));
	line++;
	ft_bzero(h->prog_name, PROG_NAME_LENGTH);
	ft_strccpy(h->prog_name, line, 34);
	write(a->fd_cor, &(h->prog_name), sizeof(h->prog_name));
}

void 	header_comment(char *line, t_header *h, t_asm *a)
{
	skip_space(&line);
	ft_printf("{7}%s\n", line);
}

int 	header_parser(char *line, t_header *h, t_asm *a)
{
	a->len_line = ft_strlen(line) + 1;
	skip_space(&line);
	if (!ft_strncmp(line,NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		header_name(line + ft_strlen(NAME_CMD_STRING), h, a);
	if (!ft_strncmp(line,COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		header_comment(line + ft_strlen(COMMENT_CMD_STRING), h, a);
	return (0);
}

void 	header_champ(t_asm *a, t_header *h)
{
	char	*line;

	a->count_line = 1;
	while (get_next_line(a->fd_champ, &line))
	{
		if (*line != COMMENT_CHAR)
			header_parser(line, h, a);
		a->count_line++;
	}
	// char *line;
	// ft_bzero(name, PROG_NAME_LENGTH + 1);
	// ft_strcpy(name,"zork");
	// // write(a->fd_cor, &name, sizeof(name));
	// ft_strcpy(name,"zork");
	// ft_bzero(name + 4, (PROG_NAME_LENGTH + 1) - 4);
	// print_memory(name,PROG_NAME_LENGTH + 1);
	// while (get_next_line(a->fd_champ,&line))
	// {
	// 	ft_printf("{8}%s\n",line);
	// }
}