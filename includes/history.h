/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:23:18 by bviala            #+#    #+#             */
/*   Updated: 2018/03/26 12:44:06 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HISTORY_H
# define __HISTORY_H

# define HIST_FILE ".cedychou_history"

# include "ft_sh.h"

/*
**		MOVE IN HISTORY
*/
int		check_history_access(const char *file);
void	close_history(t_buf *cmd);
void	close_history_noaccess(t_buf *cmd);
char	history_do(t_buf *cmd, t_read *info, t_key *entry);
char	history_mode(t_buf *cmd, t_read *info, t_key *entry);
char	history_up(t_buf *cmd, t_read *info, t_key *entry);
char	history_well_formated(char *line);
void	init_history(void);
char	no_history_do(t_buf *cmd, t_read *info, int first);
char	no_history_up(t_buf *cmd, t_read *info, int last);

/*
** 		SEARCH IN HISTORY
*/
void	history_search_nb(t_buf *cmd, t_read *info, int nb);
void	history_search_nb_neg(t_buf *cmd, t_read *info, int nb);
void	history_search_contain_name(t_buf *cmd, t_read *info, char *str);
void	history_search_begin_name(t_buf *cmd, t_read *info, char *str);
char	history_ctrlr(t_buf *cmd, t_read *info, t_key *entry);
void	ft_clear_prompt(t_read *info, int first, size_t pos, char *new);

/*
**		CHANGE MODE IN STATE MACHINE
*/
char	history_to_completion(t_buf *cmd, t_read *info, t_key *entry);
char	history_to_normal_char(t_buf *cmd, t_read *info, t_key *entry);
#endif
