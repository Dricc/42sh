/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:32:01 by maastie           #+#    #+#             */
/*   Updated: 2018/03/27 11:49:04 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PARSER_H
# define __PARSER_H

# include "ft_sh.h"

typedef struct		s_tree
{
	struct s_tree	*father;
	struct s_tree	*previous;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_token	token;

}					t_tree;

typedef struct		s_fd
{
	char			(*fd_action)(struct s_fd *, t_list **);
	char			io_default;
	char			*left_str;
	char			*right_str;
	int				here_doc;

}					t_fd;

typedef struct		s_cmd_action
{
	t_token_id		one;
	t_tree			*(*fjob)(t_process *, t_tree *);
}					t_cmd_action;

typedef struct		s_here_list
{
	int					fd[2];
	int					num;
}					t_here;

typedef struct		s_valid_res
{
	t_token_id		one;
	t_token_id		two;
}					t_valid_res;

typedef struct		s_for_close
{
	t_token_id		one;
	t_token_id		two;
}					t_for_close;

typedef struct		s_execpted
{
	t_token_id		one;
	t_token_id		two;
}					t_execpted;

typedef struct		s_classic
{
	t_token_id		one;
	t_token_id		two;
	t_tree			*(*cmp)(t_tree *, t_tree *);
	t_tree			*(*here)(t_tree *, t_tree *);
}					t_classic;

typedef	struct		s_builtin
{
	char			*name;
	int				(*f)(t_process *p, int argc, char **argv, char **env);
}					t_builtin;

extern t_tree		*g_head_tree;
extern t_tree		*g_current;
extern t_list		*g_here_list;

pid_t				init_pipe_run(pid_t f, int p[2][2], t_tree *c, t_tree *e);
int					exec_with_acces(char *t, t_process *p, t_job *j, char **e);
int					executor(t_job *j, t_process *p, int pipe[2][2],
	char **env);
int					get_id_max_job();
int					sh_check_fd(char *str);
int					ft_leave_parse(t_token t, int k);
int					ret_douille(int ret, t_token t);
int					clear_execute(char **path, t_process *p);
int					do_built_in(t_process *p, char **env);
int					set_for_pipe(t_tree *c, t_job *job);
int					read_parser(char **cmd, char *cur);
int					cnewline(t_token t, char **cmd, char **cur);
int					read_from_prompt(char **cmd, char **cur);
int					ft_free_node(t_tree *token);
int					ft_free_array(char **argv);
int					ft_free_tree(t_tree *c);
int					ft_free_process(t_process *p);
int					add_in_classic_tree(t_tree *cur, t_tree *new);
int					parser(char	**cmd);
int					ft_fill_for_jobs(t_tree *head);
void				do_pipe_child(int pipe[2][2], int pr, int dr);
void				pere(t_job *j, t_process *pr, int p[2][2], char **env);
void				print_process(t_process *p);
void				put_job_at_head_in_job_order(t_job *job);
void				put_job_at_end_in_first_job(t_job *job);
void				print_first_job();
void				print_job_order();
void				print_job(t_job *job);
void				execute_job(t_job *job);
void				wait_multiple_proc(t_list *pid_list, t_job *job);
void				remove_here_list(void);
void				init_current_process(t_tree *c, t_job *job);
void				execute_job_with_fork(t_job *j, char **env);
void				clear_assign_word(t_tree *cur, t_tree *new);
char				sh_dless(t_fd *fd_list, t_list **open_fd);
char				modify_io_child(t_process *p);
char				sh_greatand(t_fd *fd_list, t_list **open_fd);
char				sh_lessand(t_fd *fd_list, t_list **open_fd);
char				sh_less(t_fd *fd_list, t_list **open_fd);
char				sh_dgreat(t_fd *fd_list, t_list **open_fd);
char				sh_great(t_fd *fd_list, t_list **open_fd);
char				sh_lessgreat(t_fd *fd_list, t_list **open_fd);
char				*add_it_spaced(char *dst, char *src);
char				*extrac_from_backtite(char *dst, char *ref);
char				*get_command(char *ret, t_tree *chead);
char				**get_new_argv(char **argv, char *to_add);
char				**extract_from_tab(char **env, char *ref);
char				**how_to_do(char **argv, char *cmd);
char				**add_to_argv(char **argv, char *to_add);
char				**concat_tab_for_sub(char **argv, char **k, int size);
char				**sub_shell_main(char **argv, char *cmd);
t_process			*init_process(t_process *p);
t_job				*need_norme(t_job *j);
t_job				*get_new_job(t_tree *c, int exit_status, int fg);
t_job				*create_new_job(t_tree *c);
t_tree				*cpy_from_tree(t_tree *c);
t_tree				*next_on_tree(t_tree *c, int exit_status);
t_tree				*split_cmd_jobs(t_tree *c, int if_fg);
t_tree				*execute_run(t_tree *c, t_job *job, t_list *lst);
t_tree				*new_success_or_if(t_tree *c);
t_tree				*get_new_from_failure_and(t_tree *c);
t_tree				*set_fd_in_process(t_process *p, t_tree *c);
t_tree				*here(t_tree *current, t_tree *new);
t_tree				*init_node(t_token c, t_tree *n);
t_tree				*subshell(t_process *p, t_tree *c);
t_tree				*set_data_for_fill(t_tree *c, t_process *p);
t_tree				*modify_io(t_process *p, t_tree *clist);
t_tree				*add_in_arguments(t_process *p, t_tree *clist);
t_tree				*go_to_current_right(t_tree *cur, t_tree *new);
t_tree				*go_to_current_left(t_tree *cur, t_tree *new);
t_tree				*add_heredoc_in_process(t_process *p, t_tree *c);
void				sh_heredoc_remove(t_here *content);

#endif
