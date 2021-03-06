/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 13:36:49 by thugo             #+#    #+#             */
/*   Updated: 2018/03/20 18:23:26 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static char	**cpy_env(char **env)
{
	char	**new;
	int		i;

	new = (char **)ft_memalloc(sizeof(char *) * ((env ?
		ft_tab2dlen((const void **)env) : 0) + 1));
	i = -1;
	while (env && env[++i])
		new[i] = ft_strdup(env[i]);
	return (new);
}

static int	setup_env(t_process *p, char ***env, int argc, char **argv)
{
	int		i;
	char	*chr;
	char	*name;

	i = 0;
	while (i < argc)
	{
		if (!(chr = ft_strchr(argv[i], '=')))
			break ;
		if (chr == argv[i])
		{
			g_sh.exitstatus = 1;
			return (sh_error_bi(p->stderr, -1, 3, "env: setenv ", argv[i],
				": Invalid argument.\n"));
		}
		name = ft_strndup(argv[i], chr - argv[i]);
		ft_setenv(name, chr + 1, env);
		free(name);
		++i;
	}
	return (i);
}

static int	print_env(t_process *p, int argc, char **env)
{
	int		i;

	if (argc)
		return (0);
	i = -1;
	while (env[++i])
		ft_putendl_fd(env[i], p->stdout);
	return (1);
}

static void	exec_util(t_process *p, int argc, char **argv, char **env)
{
	char		*cmd;
	t_process	p2;

	cmd = NULL;
	if (print_env(p, argc, env))
		return ;
	ft_bzero(&p2, sizeof(t_process));
	p2.argv = argv;
	p2.stdout = p->stdout;
	p2.stderr = p->stderr;
	p2.stdin = p->stdin;
	if (ft_strchr(argv[0], '/'))
	{
		if (access(argv[0], X_OK | F_OK) != -1)
			cmd = argv[0];
	}
	else if (do_built_in(&p2, env))
		return ;
	else
		cmd = find_path(argv[0], ft_getenv(env, "PATH"));
	if (cmd)
		execve(cmd, argv, env);
	sh_error_bi(p->stderr, 0, 3, "env: command not found: ", argv[0], "\n");
	g_sh.exitstatus = EXIT_FAILURE;
}

int			builtin_env(t_process *p, int argc, char **argv, char **env)
{
	char	*options;
	int		index;
	int		ret;

	g_sh.exitstatus = 0;
	if ((index = ft_getopt(argc, argv, "i", &options)) == -1)
	{
		sh_error_bi(p->stderr, 1, 3, "env: illegal option -- ", options,
			"\nusage: env [-i] [name=value ...] [utility [argument ...]]\n");
		free(options);
		return (EXIT_FAILURE);
	}
	env = cpy_env(ft_strchr(options, 'i') ? NULL : env);
	ret = setup_env(p, &env, argc - index, argv + index);
	if (ret != -1)
		exec_util(p, argc - (index + ret), argv + index + ret, env);
	ret = g_sh.exitstatus;
	free(options);
	free_tab2d(&env);
	return (ret);
}
