/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 19:32:19 by maastie           #+#    #+#             */
/*   Updated: 2018/03/19 14:13:00 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			ft_free_node(t_tree *t)
{
	if (t && t != NULL)
		free(t);
	return (-1);
}

int			ft_free_tree(t_tree *c)
{
	t_tree	*r;
	t_tree	*tmp;

	if (!c)
		return (0);
	if (c->left)
		ft_free_tree(c->left);
	r = c;
	while (r)
	{
		tmp = r;
		ft_strdel(&tmp->token.str);
		r = r->right;
		free(tmp);
	}
	return (0);
}

int			ft_free_array(char **argv)
{
	int		i;
	char	*t;

	i = 0;
	while (argv && argv[i])
	{
		t = argv[i++];
		free(t);
	}
	if (argv)
		free(argv);
	return (0);
}

void		sh_free_fd_list(void *content, size_t size)
{
	t_fd	*tmp;

	(void)size;
	tmp = content;
	free(tmp->right_str);
	free(tmp->left_str);
	free(content);
}

int			ft_free_process(t_process *p)
{
	t_process	*l;

	while (p)
	{
		l = p;
		ft_free_array(p->argv);
		ft_lstdel(&p->fd_list, &sh_free_fd_list);
		ft_lstdel(&p->open_fd, NULL);
		p = p->next;
		free(l);
	}
	return (0);
}
