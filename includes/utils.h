/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 21:58:39 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/29 15:48:14 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILS_H
# define __UTILS_H

# include "libft.h"

/* DEFINE ESCAPE */
# define	SH_IS_ESC(str, i) (*(str + i) & 1)
# define	SH_IS_END_DQ(str, i) (*(str + i) & 2)

char		sh_escape(char *str, char **escaped);
t_list		*sh_brace_exp(char *tkkn);
t_list		*sh_glob(char *to_glob);
char		*escape_it(char *str);

#endif
