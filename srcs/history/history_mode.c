/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:42:19 by bviala            #+#    #+#             */
/*   Updated: 2018/03/19 15:14:44 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		close_history(t_buf *cmd)
{
	int fd;

	g_sh.edition_state = NORMAL;
	if (ft_strcmp(cmd->cmd, "\n"))
		g_sh.history = ft_ldl_addfront(g_sh.history,
				ft_strndup(cmd->cmd, cmd->size_actual));
	if (check_history_access(g_sh.hist_file))
	{
		if (*cmd->cmd && ft_strcmp(cmd->cmd, "\n") &&
		(fd = open(g_sh.hist_file, O_RDWR | O_APPEND | O_CREAT, 0600)) > 0)
		{
			ft_putstr_fd("#", fd);
			ft_putstr_fd(cmd->cmd, fd);
			close(fd);
		}
		ft_ldl_clear(&g_sh.hist, &ft_strdel);
	}
	else
		g_sh.h_current = g_sh.history->head;
	g_sh.h_first = 0;
	ft_strdel(&(g_sh.h_save));
}

char		history_up(t_buf *cmd, t_read *info, t_key *entry)
{
	int	last;

	if (!g_sh.hist_current)
		return (0);
	last = (entry->entry[2] == 65) ? 0 : 1;
	if (!check_history_access(g_sh.hist_file))
		return (no_history_up(cmd, info, last));
	if (!last && g_sh.hist_current->next)
		g_sh.hist_current = g_sh.hist_current->next;
	else if (last)
		g_sh.hist_current = g_sh.hist->tail;
	display_str(cmd, info, g_sh.hist_current->content,
			ft_strlen(g_sh.hist_current->content));
	return (0);
}

char		history_do(t_buf *cmd, t_read *info, t_key *entry)
{
	int	first;

	if (!g_sh.hist_current)
		return (0);
	first = (entry->entry[2] == 66) ? 0 : 1;
	if (!check_history_access(g_sh.hist_file))
		return (no_history_do(cmd, info, first));
	if (!first && g_sh.hist_current->prev)
		g_sh.hist_current = g_sh.hist_current->prev;
	else if (first)
		g_sh.hist_current = g_sh.hist->head;
	display_str(cmd, info, g_sh.hist_current->content,
			ft_strlen(g_sh.hist_current->content));
	return (0);
}

static void	history_init(t_buf *cmd, t_read *info, int fd, size_t len)
{
	char	*line;

	len = (info->curs_char) ? info->curs_char : ft_strlen(cmd->cmd);
	if (!g_sh.hist)
		g_sh.hist = ft_ldl_new_list();
	if (check_history_access(g_sh.hist_file) && !(line = NULL))
	{
		while ((fd = open(g_sh.hist_file, O_RDWR)) == -1 && errno == EINTR)
			;
		if (fd == -1)
			return ;
		while ((get_next_line(fd, &line) > 0) && history_well_formated(line))
		{
			if (!info->curs_char)
				g_sh.hist = ft_ldl_addfront(g_sh.hist, ft_strdup(line + 1));
			else
			{
				if (!ft_strncmp(line + 1, cmd->cmd, len))
					g_sh.hist = ft_ldl_addfront(g_sh.hist, ft_strdup(line + 1));
			}
			ft_strdel(&line);
		}
		ft_strdel(&line);
		close(fd);
	}
}

char		history_mode(t_buf *cmd, t_read *info, t_key *entry)
{
	g_sh.edition_state = HISTORY;
	if (!g_sh.hist)
		history_init(cmd, info, -1, 0);
	g_sh.hist = ft_ldl_addfront(g_sh.hist, ft_strdup(cmd->cmd));
	g_sh.hist_current = g_sh.hist->head;
	g_sh.h_save = ft_strdup(cmd->cmd);
	return (history_up(cmd, info, entry));
}
