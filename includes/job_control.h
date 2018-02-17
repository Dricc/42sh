/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 12:53:03 by scorbion          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2018/01/23 13:44:33 by scorbion         ###   ########.fr       */
=======
/*   Updated: 2018/02/17 12:51:21 by scorbion         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include <sys/types.h>
# include <termios.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>


/* A process is a single process.  */
typedef struct	s_process
{
	struct s_process	*next;      /* next process in pipeline */
	char				**argv;		/* for exec */
	pid_t				pid;        /* process ID */
	int					completed;  /* true if process has completed */
	int					stopped;    /* true if process has stopped */
	int					status;     /* reported status value */
	int					stdin;  		// standard i/o channels 
	int					stdout;
	int					stderr;
}				t_process;

/* A job is a pipeline of processes.  */
typedef struct	s_job
{
	struct s_job	*next;			/* next andor active job */
	int				andor;
	t_process		*first_process;	/* list of processes in this job */
}				t_job;

// /* A job is a pipeline of processes.  */
// typedef struct	s_job
// {
//	int				num;
// 	char			*command;		/* command line, used for messages */
// 	char			notified;		/* true if user told about stopped job */
// 	pid_t			pgid;			/* process group ID */
// 	struct termios	tmodes;			/* saved terminal modes */
// 	t_process		*first_process;	/* list of processes in this job */
// }				t_job;


extern t_job *first_job;
extern pid_t shell_pgid;
extern struct termios shell_tmodes;
extern int shell_terminal;
extern int shell_is_interactive;

t_job	*find_job(pid_t pgid);
int		job_is_stopped(t_job *j);
int		job_is_completed(t_job *j);
void	continue_job (t_job *j, int foreground);
void	do_job_notification (void);
void	format_job_info (t_job *j, const char *status);
void	init_shell ();
void	launch_job (t_job *j, int foreground);
void	launch_process (t_process *p, pid_t pgid, int foreground, char ** env);
void	mark_job_as_running (t_job *j);
int		mark_process_status (pid_t pid, int status);
void	put_job_in_background (t_job *j, int cont);
void	put_job_in_foreground (t_job *j, int cont);
void	update_status (void);
void	wait_for_job (t_job *j);

#endif
