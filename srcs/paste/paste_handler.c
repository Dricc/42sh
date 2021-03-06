/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:10:41 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/29 04:06:07 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern size_t	g_max_char_visu;

static void	remove_excess(t_key *entry, int len)
{
	if (len <= 0 || entry->nread - len <= 0)
	{
		ft_bzero(entry, sizeof(t_key));
		return ;
	}
	ft_memmove(entry->entry, entry->entry + len, entry->nread - len);
	entry->nread -= len;
	ft_bzero(entry->entry + entry->nread, SIZE_BUFF - entry->nread - 1);
}

static int	paste_end(char test)
{
	static int	i;
	const char	paste_finish[6] = {'\e', '[', '2', '0', '1', '~'};

	if (test == paste_finish[i])
	{
		i = (i == 5) ? 0 : i + 1;
		return ((i ? 0 : -1));
	}
	else
	{
		i = 0;
		return (1);
	}
}

void		insert_chars_pasted_in(t_buf *cmd, t_read *info, t_buf *pasted)
{
	char	*curs;
	int		len;
	int		size_pasted;

	size_pasted = ft_strlen(pasted->cmd);
	len = sh_curs_unicode(cmd->cmd, info->curs_char, 0);
	curs = cmd->cmd + len;
	ft_memmove(curs + size_pasted, curs, ft_strlen(curs));
	ft_memcpy(curs, pasted->cmd, size_pasted);
	cursor_back_home(info, 1);
	write(g_sh.fd_tty, cmd->cmd, len);
	tputs(g_termcaps_cap[HIGH_START], 0, &ft_putchar_termcap);
	write(g_sh.fd_tty, curs, size_pasted);
	tputs(g_termcaps_cap[HIGH_STOP], 0, &ft_putchar_termcap);
	write(g_sh.fd_tty, curs + size_pasted, cmd->size_actual - len
			- size_pasted);
}

void		insert_chars_pasted(t_buf *cmd, t_read *info, t_buf *pasted)
{
	int		i;

	i = -1;
	while (*(pasted->cmd + (++i)))
		if (ft_isspace(*(pasted->cmd + i)))
			*(pasted->cmd + i) = ' ';
	if (!buff_handler(cmd, NULL, pasted->cmd, info))
		return ;
	pasted->size_actual = ft_strlen(pasted->cmd);
	cmd->size_actual += pasted->size_actual;
	if (info->curs_char == (long)info->total_char)
	{
		ft_strncat(cmd->cmd, pasted->cmd, pasted->size_actual);
		tputs(g_termcaps_cap[HIGH_START], 0, &ft_putchar_termcap);
		write(g_sh.fd_tty, pasted->cmd, pasted->size_actual);
		tputs(g_termcaps_cap[HIGH_STOP], 0, &ft_putchar_termcap);
	}
	else
		insert_chars_pasted_in(cmd, info, pasted);
	info->curs_char += ft_strlen_utf8(pasted->cmd);
	info->total_char = ft_strlen_utf8(cmd->cmd);
	cursor_display_update(info, 1);
}

char		paste_handler(t_buf *cmd, t_read *info, t_key *entry)
{
	int		i;
	int		ret;
	t_buf	pasted;
	char	*space;
	char	stop;

	stop = 0;
	i = 6;
	init_paste_handler(&space, &pasted, info);
	while ((ret = paste_end(entry->entry[i])) >= 0)
	{
		if (pasted.size_actual > pasted.size_max - 2 &&
				!buff_handler(&pasted, NULL, space, info))
			stop = 1;
		if (!stop)
			(ret == 1) && (pasted.cmd[pasted.size_actual++] =
					*(entry->entry + i));
		else
			(ret == 1) && ++pasted.size_actual;
		read_and_bzero(entry, &i);
	}
	insert_chars_pasted(cmd, info, &pasted);
	remove_excess(entry, i + 1);
	ft_xfree(2, pasted.cmd, space);
	return (1);
}
