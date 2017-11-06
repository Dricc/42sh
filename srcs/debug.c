/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:48:05 by czalewsk          #+#    #+#             */
/*   Updated: 2017/11/06 15:57:26 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <fcntl.h>

# define DEBUG_WINDOW ("/dev/ttys005")

int		debug(char *format, ...)
{
	int			fd;
	va_list		ap;

	fd = open(DEBUG_WINDOW, O_RDWR);
	va_start(ap, format);
	vdprintf(fd, format, ap);
	va_end(ap);
	close(fd);
	return (1);
}