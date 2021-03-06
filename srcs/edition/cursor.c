/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 20:48:25 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/29 19:27:54 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int		g_move = 1;

static int		calcul_line(t_read *info, int write)
{
	static int		line;
	int				line_max;
	int				ret;

	ret = 0;
	if (write)
	{
		g_move = 1;
		line = (info->curs_char + info->prompt) / info->win_co;
		line_max = (info->total_char + info->prompt - 1) / info->win_co;
		ret = line - line_max;
	}
	else
	{
		line_max = (info->curs_char + info->prompt) / info->win_co;
		ret = line_max - line;
		line = line_max;
	}
	return (ret);
}

void			cursor_display_update(t_read *info, int write)
{
	int		line;
	int		col;

	if (!info->win_co)
		return ;
	if (((info->curs_char + info->prompt + 1) / info->win_co == info->win_co))
		col = 0;
	else
		col = (info->curs_char + info->prompt) % info->win_co;
	line = calcul_line(info, write);
	if (line == 1)
		tputs(g_termcaps_cap[DOWN], 0, &ft_putchar_termcap);
	else if (line)
		tputs(tparm(g_termcaps_cap[line < 0 ? NUP : NDO], ABS(line)), 1,
			&ft_putchar_termcap);
	tputs(tparm(g_termcaps_cap[COL], col), 0, &ft_putchar_termcap);
}

char			curs_move_hz(t_buf *cmd, t_read *info, t_key *entry)
{
	int		mvt;

	(void)cmd;
	mvt = (entry->entry[2] == 68 ? -1 : 1);
	g_move = 1;
	if (info->curs_char + mvt > (long)info->total_char
			|| info->curs_char + mvt < 0)
		return (0);
	g_move = 1;
	info->curs_char += mvt;
	cursor_display_update(info, 0);
	ft_bzero(entry, sizeof(t_key));
	return (1);
}

char			curs_move_vt(t_buf *cmd, t_read *info, t_key *entry)
{
	static long		old_pos;
	long			new_pos;
	long			line;

	(void)cmd;
	if (g_move)
	{
		old_pos = info->curs_char;
		g_move = 0;
	}
	new_pos = old_pos + (entry->entry[5] == 66 ? info->win_co : -info->win_co);
	line = ((info->curs_char + info->prompt) / (info->win_co));
	if (!(new_pos < -(long)info->prompt
			|| ((new_pos > (long)info->total_char) &&
			(long)((info->total_char + info->prompt) / info->win_co) == line)))
		old_pos = new_pos;
	else
		return (0);
	info->curs_char = old_pos;
	if (info->curs_char < 0 || info->curs_char > (long)info->total_char)
		info->curs_char = (info->curs_char < 0 ? 0 : info->total_char);
	cursor_display_update(info, 0);
	ft_bzero(entry, sizeof(t_key));
	return (1);
}

char			edition_home_end(t_buf *cmd, t_read *info, t_key *entry)
{
	(void)cmd;
	if (!cmd->size_actual)
		return (0);
	g_move = 1;
	if (entry->entry[2] == 72 && info->curs_char > 0)
	{
		info->curs_char = 0;
		cursor_display_update(info, 0);
	}
	else if (entry->entry[2] == 70 && info->curs_char != (long)info->total_char)
	{
		info->curs_char = info->total_char;
		cursor_display_update(info, 0);
	}
	ft_bzero(entry, sizeof(t_key));
	return (1);
}
