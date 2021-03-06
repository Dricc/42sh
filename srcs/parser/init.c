/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:51:09 by maastie           #+#    #+#             */
/*   Updated: 2018/03/13 17:26:21 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_tree		*init_node(t_token c, t_tree *n)
{
	n = (t_tree *)ft_memalloc(sizeof(t_tree));
	n->token = c;
	return (n);
}

int			ret_douille(int ret, t_token t)
{
	if (ret == -1)
		return (ft_leave_parse(t, 0));
	return (-1);
}
