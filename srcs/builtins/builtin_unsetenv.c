/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 07:32:03 by thugo             #+#    #+#             */
/*   Updated: 2018/03/23 14:16:00 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int		builtin_unsetenv(t_process *p, int argc, char **argv, char **env)
{
	(void)env;
	if (argc == 1)
	{
		return (sh_error_bi(p->stderr, EXIT_FAILURE, 1,
			"unset[env]: Too few arguments.\n"));
	}
	while (*(++argv))
		env_unset(*argv);
	return (EXIT_SUCCESS);
}
