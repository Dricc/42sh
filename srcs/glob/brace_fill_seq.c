/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace_fill_seq.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 07:08:35 by czalewsk          #+#    #+#             */
/*   Updated: 2017/12/14 09:16:02 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

void	brace_fill_seq_choice(char *str, char *end, t_brace_exp *valide,
		unsigned char *closed)
{
	size_t			s;
	unsigned char	c;
	int				i;
	int				start;

	i = valide->begin - str;
	start = i + 1;
	c = *(closed + i);
	s = 1;
	while ((str + ++i) <= end)
	{
		if (*(closed + i) == c || (str + i) == end)
		{
			ft_lstaddback(&valide->word, ft_lstnew_str(
						ft_strsub(str, start, s - 1), sizeof(char*)));
			start = i + 1;
			s = 0;
		}
		s++;
	}
	/* DEBUG */
	t_list *tmp = valide->word;
	write(1, "\n", 1);
	while (tmp)
	{
		ft_printf("Word=%s|\n", tmp->content);
		tmp = tmp->next;
	}
	/* END */
}

void	brace_fill_seq_num(char *str, t_brace_exp *valide)
{
	int		i;
	long	l;

	(void)str;
	l = ft_atol(valide->begin + 1);
	i = valide->nb[0];
	if (valide->nb[0] > 11 || l > INT_MAX || l < INT_MIN)
		valide->nb[0] = (*(valide->begin + 1) == '-') ? INT_MIN : INT_MAX;
	else
		valide->nb[0] = l;
	l = ft_atol(valide->begin + i + 2 + 1);
	if (valide->nb[1] > 11 || l > INT_MAX || l < INT_MIN)
		valide->nb[1] = (*(valide->begin + 1 + i + 2) == '-') ?
			INT_MIN : INT_MAX;
	else
		valide->nb[1] = l;
	/* DEBUG */
	ft_printf("\nBorne=%d|%d\n", valide->nb[0], valide->nb[1]);
	/* END */
}