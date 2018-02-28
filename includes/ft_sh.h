/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:15:01 by czalewsk          #+#    #+#             */
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
# include "job_control.h"
# include "expansions.h"
# include "lexer.h"
# include "lexer_types.h"
# include "env.h"
# include "parser.h"
# include "utils.h"
# include "history.h"
# include "builtins.h"
# include "completion.h"

/*
** Structure globale, comprenant les informations relatives a :
** - l'etat de l'edition de ligne (normal, auto-completion ou historique)
** - l'historique des arguments en ligne de commande
** - l'autocompletion
** - le statut de sortie de la commande precedente (SUCCESS ou Code d'erreur)
** - le copycolle
*/
typedef struct			s_sh
{
	int				edition_state;
	int				fd_tty;
	t_ldl_head		*hist;
	t_ldl			*hist_current;
	t_ldl_head		*history;
	t_ldl			*h_current;
	char			*h_save;
	char			*hist_file;
	int				h_first;
	int				fds[3];
	char			**env;
	int				exitstatus;
	t_comp			*comp;
	char			comp_status;
	int				comp_start;
	int				comp_end;
	int				test_fd;// read.c25.18 a modifier si necessaire // ft_sh.c:48:7: a laisser c est pour reset la STDIN sur le tty
	char			*pasted;
	char			prompt_display;

}						t_sh;

extern t_sh				g_sh;

/*
** Variable permettant decrire les term sur le bon fd (ft_putchar_termcap)
*/
extern int	g_termcps_fd;

# define SIZE_BUF_CMD (128)
# define PROMPT ("✗ ")
#endif
