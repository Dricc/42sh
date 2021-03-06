/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 16:06:24 by maastie           #+#    #+#             */
/*   Updated: 2018/03/29 00:58:23 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int				exec_in_line(t_job *job, t_process *p, char **env)
{
	if (access(p->argv[0], X_OK | F_OK) != -1)
	{
		exec_with_acces(p->argv[0], p, job, env);
		return (0);
	}
	return (1);
}

int				exec_with_acces(char *t, t_process *p, t_job *j, char **e)
{
	if (j->foreground)
		termcaps_restore_tty();
	launch_process(t, p, j, e);
	return (g_sh.exitstatus);
}

int				executor(t_job *j, t_process *p, int pipe[2][2], char **env)
{
	char		*exec_line;
	int			i;

	i = 0;
	exec_line = NULL;
	do_pipe_child(pipe, j->process == p, !p->next);
	if (!modify_io_child(p))
		exit(EXIT_FAILURE);
	if (!p->argv)
		exit(EXIT_FAILURE);
	if (do_built_in(p, env))
		exit(g_sh.exitstatus);
	if (ft_strstr(p->argv[0], "/") || ft_strstr(p->argv[0], "./"))
	{
		if (exec_in_line(j, p, env) == 0)
			exit(EXIT_FAILURE);
	}
	else if ((exec_line = find_path(p->argv[0], ft_getenv(env, "PATH"))))
	{
		exec_with_acces(exec_line, p, j, env);
		exit(g_sh.exitstatus);
	}
	ft_strdel(&exec_line);
	sh_error(0, 0, NULL, 3, "command not found: ", p->argv[0], "\n");
	exit(EXIT_FAILURE);
}

void			execute_job(t_job *job)
{
	char		**env;
	t_list		*tmp;

	if (job == NULL)
		return ;
	env = env_make(ENV_GLOBAL | ENV_TEMP);
	if (!job->process->next && job->foreground && job->process->argv &&
	ft_strcmp(job->process->argv[0], "env") && do_built_in(job->process, env))
	{
		job->is_builtin = 1;
		job->status_last_process = g_sh.exitstatus;
	}
	else
	{
		execute_job_with_fork(job, env);
		if (job->foreground)
			put_job_at_head_in_job_order(job);
		else
		{
			tmp = ft_lstnew(NULL, 0);
			tmp->content = job;
			ft_lstinsert_if_end(&g_job_order, tmp, add_after_stopped);
		}
		put_job_at_end_in_first_job(job);
	}
}

void			execute_job_with_fork(t_job *j, char **env)
{
	t_process	*pr;
	int			p[2][2];

	ft_memset(p, -1, sizeof(int[2][2]));
	pr = j->process;
	while (pr)
	{
		if (pr != j->process)
			close(p[1][1]);
		if (pr->next && pipe(p[0]) == -1)
		{
			exit(sh_error(1, 0, NULL, 1, "Fail to create pipe.\n"));
			return ;
		}
		p[1][1] = p[0][1];
		if ((pr->pid = fork()) == -1)
		{
			exit(sh_error(1, 0, NULL, 1, "Fail to fork.\n"));
			return ;
		}
		pere(j, pr, p, env);
		pr = pr->next;
	}
}
