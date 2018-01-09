/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compatibility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 16:08:24 by maastie           #+#    #+#             */
/*   Updated: 2017/12/14 16:08:25 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_tree		*go_to_current_right(t_tree *cur, t_tree *new)
{
	new->previous = cur;
	cur->right = new;
	return (new);
}

t_tree		*go_to_current_left(t_tree *cur, t_tree *new)
{
	t_tree	*tmp;

	tmp = cur;
	while (tmp->previous)
		tmp = tmp->previous;
	tmp->left = new;
	new->father = tmp;
	return (new);
}