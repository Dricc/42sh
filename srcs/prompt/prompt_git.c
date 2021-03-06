/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_git.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 00:33:56 by bviala            #+#    #+#             */
/*   Updated: 2018/03/07 17:23:13 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static char	sh_print_git(int fd)
{
	char	*line;
	char	*actual_head;
	int		ret;
	int		ret_length;

	ret_length = -1;
	line = NULL;
	if ((ret = get_next_line(fd, &line)) > 0)
	{
		if ((actual_head = ft_strrchr(line, '/')))
		{
			ft_putstr_fd(BLUE " git:(" RED, g_sh.fd_tty);
			ft_putstr_fd(actual_head + 1, g_sh.fd_tty);
			ft_putstr_fd(BLUE ")" C_DEFAULT, g_sh.fd_tty);
			ret_length = ft_strlen(actual_head + 1) + 7;
		}
		ft_strdel(&line);
	}
	close(fd);
	get_next_line(-2, NULL);
	return (ret_length);
}

int			sh_prompt_git(int ret, int depth)
{
	int		fd;
	char	*path;
	char	*test_git;

	path = NULL;
	if (!(path = getcwd(path, 0)))
		return (0);
	depth = ft_howmany(path, '/');
	test_git = ft_strdup("./.git/HEAD");
	while (--depth >= 0)
	{
		while ((fd = open(test_git, O_RDONLY)) == -1 && errno == EINTR)
			;
		if (fd > 0)
		{
			ret = sh_print_git(fd);
			depth = -1;
		}
		test_git = ft_strjoin_free("../", test_git, 1);
	}
	ft_strdel(&test_git);
	ft_strdel(&path);
	return ((ret != -1) ? ret : 0);
}
