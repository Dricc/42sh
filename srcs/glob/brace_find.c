/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 09:30:11 by czalewsk          #+#    #+#             */
/*   Updated: 2018/02/15 06:08:00 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

char			brace_find_end(t_brace_check *brace, char **curs, char *tkkn)
{
	if (**curs == '\\')
	{
		(*curs) += (*((*curs) + 1)) ? 2 : 1;
		return (1);
	}
	if (**curs == '}' && !*(brace->closed + (*curs - tkkn)))
	{
		if (!brace->already_close)
			*(brace->closed + (*curs - tkkn)) = 255;
		brace->already_close = 1;
		return (2);
	}
	if (!**curs)
	{
		*curs = brace->last_beg - 1;
		return (*curs <= tkkn ? 126 : 0);
	}
	(*curs)++;
	return (1);
}

char			brace_find_beg(t_brace_check *brace, char **curs, char *tkkn)
{
	if (!*curs || (*curs != tkkn && *(*curs - 1) == '\\'))
	{
		if (!*curs || (*curs - 2 < tkkn))
			return (124);
		(*curs) -= 2;
	}
	if (**curs == '{' && !ft_is_escape(*curs, tkkn))
	{
		brace->last_beg = *curs;
		brace->already_close = 0;
		(*curs)++;
		return (1);
	}
	if (*curs == tkkn)
		return (125);
	(*curs)--;
	return (0);
}

t_brace_exp		brace_find_pattern(char *tkkn)
{
	int				i;
	char			*curs;
	t_brace_check	brace;
	char			state;
	char			(*const f[3])() =
	{&brace_find_beg, &brace_find_end, &brace_valide_type};

	ft_bzero(&brace, sizeof(t_brace_check));
	i = ft_strlen(tkkn);
	brace.closed = ft_memalloc(i + 1);
	curs = (tkkn + i);
	state = 0;
	while (state <= 4)
		state = f[(int)state](&brace, &curs, tkkn);
	if (brace.valide.mode == 1)
		brace_fill_seq_choice(tkkn, brace.valide.end,
				&brace.valide, brace.closed);
	else if (brace.valide.mode == 3)
		brace_fill_seq_num(&brace.valide);
	ft_strdel((char**)&brace.closed);
	return (brace.valide);
}
