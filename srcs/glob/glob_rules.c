/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_rules.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 15:12:09 by czalewsk          #+#    #+#             */
/*   Updated: 2018/01/17 13:08:00 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_glob.h"

t_glob_rules (*const	g_f[4])(char **, t_list **, char) = {glob_rules_char,
	glob_rules_asterisk, glob_rules_question, glob_rules_square};

t_glob_rules			glob_rules_char(char **curs, t_list **rules, char add)
{
	t_glob_rules	rule;

	ft_bzero(&rule, sizeof(t_glob_rules));
	rule.single = 1;
	if (**curs == '/')
	{
		rule.directory = 1;
		++(*curs);
	}
	rule.in[(unsigned int)**curs] = 1;
	if (add)
	{
		ft_memset(&rule.out, 1, 255);
		rule.out[(unsigned int)**curs] = 0;
		ft_lstaddback(rules, ft_lstnew(&rule, sizeof(t_glob_rules)));
	}
	++(*curs);
	return (rule);
}

t_glob_rules			glob_rules_question(char **curs, t_list **rules,
		char add)
{
	t_glob_rules	rule;

	ft_bzero(&rule, sizeof(t_glob_rules));
	rule.single = 1;
	ft_memset(&rule.in, 1, 255);
	rule.in[0] = 0;
	rule.out[0] = 1;
	rule.in['.'] = 0;
	rule.out['.'] = 1;
	if (add)
		ft_lstaddback(rules, ft_lstnew(&rule, sizeof(t_glob_rules)));
	++(*curs);
	return (rule);
}

t_glob_rules			glob_rules_asterisk(char **curs, t_list **rules,
		char add)
{
	t_glob_rules	rule;
	int				i;

	(void)add;
	ft_bzero(&rule, sizeof(t_glob_rules));
	if (**curs == '\\')
		(*curs)++;
	while ((i = glob_check_char(**curs)) == 1)
		(*curs)++;
	rule = g_f[i](curs, rules, 0);
	rule.single = 0;
	ft_lstaddback(rules, ft_lstnew(&rule, sizeof(t_glob_rules)));
	return (rule);
}

void					sh_glob_rules_init(char *str, t_list **rules)
{
	char			*end;
	t_glob_rules	rule;

	end = str;
	while (*end)
		end++;
	while (str <= end)
	{
		if (*str == '\\')
			str++;
		g_f[(int)glob_check_char(*str)](&str, rules, 1);
	}
	if (!((t_glob_rules*)(*rules)->content)->in['.'])
	{
		ft_bzero(&rule, sizeof(t_glob_rules));
		rule.out['.'] = 1;
		rule.single = 1;
		ft_memset(&rule.in, 1, 255);
		rule.in['.'] = 0;
		ft_lstadd(rules, ft_lstnew(&rule, sizeof(t_glob_rules)), 0);
	}
}
