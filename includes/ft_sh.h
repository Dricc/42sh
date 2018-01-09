/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:15:01 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/09 14:50:37 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_SH_H
# define __FT_SH_H

# include "libft.h"
# include <termcap.h>
# include <curses.h>
# include <term.h>
# include <stdlib.h>
# include <wctype.h>
# include <string.h>
# include <errno.h>
# include <xlocale.h>
# include <locale.h>
# include <wctype.h>
# include "edition.h"
# include "termcaps.h"
# include "prompt.h"
# include "utils.h"
# include "history.h"
# include "builtins.h"

/*
** Define :D
*/
typedef struct			s_sh
{
	int			edition_state;
	t_ldl_head	*hist;
	t_ldl		*hist_current;
	t_ldl_head	*history;
	t_ldl		*h_current;
	char		*h_save;
	char		*hist_file;
	int			h_first;
	char		**env;
}						t_sh;

extern t_sh				g_sh;

# define SIZE_BUF_CMD (128)
# define PROMPT ("Cedychou_sh : ")
// (canard) <U+1F986> A remettre dans le prompt
#endif
