/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expoint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 16:30:15 by thugo             #+#    #+#             */
/*   Updated: 2018/03/12 04:18:17 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void make_tokens(t_list **lst, char *expand)
{
	char	**split;
	int		i;

	split = ft_strsplits(expand, " \t\n");
	i = -1;
	while (split[++i])
		expansions_addtoken(lst, split[i], WORD);
	free(split);
	free(expand);
}

char	expand_history_expoint(const t_token *tk, t_list **lst)
{
	char	*expoint;
	char	*expand;
	char	*start;

	ft_printf("DEBUG TK: '%s'\n", tk->str);
	expoint = tk->str;
	while (*expoint && (expoint = ft_strchr(expoint, '!')) &&
			ft_is_escape(expoint, tk->str))
		++expoint;
	if (!expoint)
		return (0);
	ft_printf("Expoint: '%s'\n", expoint);
	if (!(expand = history_expoint(expoint))){
		ft_printf("ERREUR EVENT NOT FOUND\n");
		return (0);}
	if (expoint == tk->str)
		make_tokens(lst, expand);
	else
	{
		start = ft_strndup(tk->str, expoint - tk->str);
		make_tokens(lst, ft_strjoin_free(start, expand, 2));
	}
	return (1);
}
