/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 22:19:11 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/25 23:47:16 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_label_name(char *s)
{
	int		i;
	int		good;
	int		len;

	i = 0;
	len = 0;
	good = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(LABEL_CHARS, s[i]))
			good++;
		else if ((s[i] == DIRECT_CHAR || s[i] == ' ' || s[i] == SEPARATOR_CHAR) && s[i + 1] == '-')
		{
			if (!(ft_isdigit(s[i + 2]) || !(ft_strchr(LABEL_CHARS, s[i + 2]))))
				return (i);
			i += 2;
		}
		else if (s[i] != LABEL_CHAR && s[i] != DIRECT_CHAR && s[i] != SEPARATOR_CHAR && !ft_strchr(SP, s[i]))
			return (i);
		i++;
	}
	return (0);
}

int		check_first(char c)
{
	if (!ft_strchr(LABEL_CHARS, c))
		return (1);
	return (0);
}

void handles_comment(char **s)
{
	char *tmp;
	int i;
	int len;

	i = 0;
	tmp = *s;
	while((*s)[i] != '\0' && (*s)[i] != COMMENT_CHAR)
		i++;
	if (i == ft_strlen(tmp))
		return ;
	len  = ft_strlen((*s) + i );
	ft_bzero((*s) + i, len);
	// ft_printf("{9}%d - %d - %s\n",len, i, *s);
}

void	check_label(char *s, t_lab *lab, t_asm *a)
{
	int		i;
	int		len;
	char	*name;

	i = 0;
	name = NULL;
	lab->colon = a->count_line;
	lab->line = ft_strlen(s);
	a->len_line = skip_space(&s);
	if (*s == COMMENT_CHAR)
		return ;

	len = ft_strlchr(s, LABEL_CHAR);
	if (check_first(*s))
		return (lexical_error(a->count_line, 1));
	handles_comment(&s);
	// ft_printf("{9}%s\n",s);
	if ((i = check_label_name(s)) || *s == ':')
		return (lexical_error(a->count_line, i + a->len_line));
	if (len == 0 && *s != ':')
	{
		if (*s == '\0')
			return ;
		return (get_cmd(lab, s, a));
	}
	if ((s[len - 1] == DIRECT_CHAR || ft_strchr(SP, s[len - 1])) && ft_strchr(LABEL_CHARS, s[len + 1]))
		return (get_cmd(lab, s, a));
	name = ft_strndup(s, len);
	add_back_lab(&lab, name, a);
	a->nb_label++;
	s = s + len + 1;
	skip_space(&s);
	if (*s != '\0')
		get_cmd(lab, s, a);
}

t_lab	*get_label(t_asm *a)
{
	char	*line;
	t_lab	*lab;

	lab = NULL;
	add_back_lab(&lab, "@@", a);
	// a->count_line += 1;
	while (get_next_line(a->fd_champ, &line) > 0)
	{
		if (*line != COMMENT_CHAR && *line != '\0')
			check_label(line, lab, a);
		a->count_line++;
		free(line);
	}
	remove_first_label(a, &lab);
	a->label = add_label(&lab, a);
	return (lab);
}
