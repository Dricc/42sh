/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:23:18 by bviala            #+#    #+#             */
/*   Updated: 2017/12/01 20:05:29 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HISTORY_H
# define __HISTORY_H

# define HIST_FILE "/Users/bviala/.cedychou_history"

# include "ft_sh.h"

int		check_history_access(const char *file);	
char	history_mode(t_buf *cmd, t_read *info, t_key *entry);
char	sh_validate_line_history(t_buf *cmd, t_read *info, t_key *entry);
#endif
