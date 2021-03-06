/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 20:56:27 by thugo             #+#    #+#             */
/*   Updated: 2018/03/01 21:20:53 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

size_t		env_len(const t_env **env, char type)
{
	size_t	len;
	int		i;

	len = 0;
	i = -1;
	while (env[++i])
		if (env[i]->type & type)
			++len;
	return (len);
}
