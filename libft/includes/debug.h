/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:00:09 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/08 13:54:02 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __DEBUG_H
# define __DEBUG_H

# include "libft.h"
# include <fcntl.h>

# define DEBUG_WINDOW ("/dev/ttys005")
# define DEBUG(x...) (debug(x));

int		debug(char *format, ...);

#endif
