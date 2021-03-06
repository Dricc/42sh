/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 19:24:19 by bviala            #+#    #+#             */
/*   Updated: 2018/03/19 15:09:16 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		history_to_normal_char(t_buf *cmd, t_read *info, t_key *entry)
{
	(void)entry;
	(void)cmd;
	(void)info;
	ft_ldl_clear(&g_sh.hist, &ft_strdel);
	g_sh.h_first = 0;
	g_sh.hist_current = NULL;
	g_sh.h_current = g_sh.history->head;
	ft_strdel(&(g_sh.h_save));
	g_sh.edition_state = NORMAL;
	return (1);
}

char		history_to_completion(t_buf *cmd, t_read *info, t_key *entry)
{
	ft_ldl_clear(&g_sh.hist, &ft_strdel);
	g_sh.h_first = 0;
	g_sh.h_current = g_sh.history->head;
	ft_strdel(&(g_sh.h_save));
	g_sh.edition_state = NORMAL;
	return (key_manager(cmd, info, entry));
}
