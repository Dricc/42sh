/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 19:44:57 by maastie           #+#    #+#             */
/*   Updated: 2018/03/29 02:05:15 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			sh_check_fd(char *str)
{
	int		ret;

	if (ft_memcmp(str, "-", 1) == 0)
		return (-1);
	if (!ft_isint(str))
		return (sh_error(-2, 0, NULL, 2, str, ": Bad file descriptor\n"));
	ret = ft_atoi(str);
	if (ret <= 10)
		return (ret);
	return (sh_error(-1, 0, NULL, 3, "Error in redirection, number ", str,
		" must be between 0 and 10\n"));
}

char		sh_lessand(t_fd *test_fd, t_list **open_fd)
{
	int		lfd;
	int		rfd;

	(void)open_fd;
	rfd = sh_check_fd(test_fd->right_str);
	if ((lfd = test_fd->io_default ? 0 : sh_check_fd(test_fd->left_str)) == -2)
		return (-1);
	if (rfd == -1)
		close(lfd);
	else
	{
		rfd = dup(rfd);
		if (dup2(rfd, lfd) == -1)
			return (-1);
	}
	ft_lstadd(open_fd, ft_lstnew(&rfd, sizeof(int)), 0);
	ft_lstadd(open_fd, ft_lstnew(&lfd, sizeof(int)), 0);
	return (0);
}

char		sh_greatand(t_fd *test_fd, t_list **open_fd)
{
	int		lfd;
	int		rfd;

	rfd = sh_check_fd(test_fd->right_str);
	if ((lfd = test_fd->io_default ? 1 : sh_check_fd(test_fd->left_str)) == -2)
		return (-1);
	if (rfd == -1)
		close(lfd);
	else
	{
		rfd = dup(rfd);
		if (dup2(rfd, lfd) == -1)
			return (-1);
	}
	ft_lstadd(open_fd, ft_lstnew(&rfd, sizeof(int)), 0);
	ft_lstadd(open_fd, ft_lstnew(&lfd, sizeof(int)), 0);
	return (0);
}

char		sh_lessgreat(t_fd *test_fd, t_list **open_fd)
{
	int		lfd;
	int		rfd;

	if ((rfd = open(test_fd->right_str, O_RDWR | O_CREAT, 0644)) == -1)
		return (1);
	if (test_fd->io_default)
		lfd = 0;
	else
		lfd = sh_check_fd(test_fd->left_str);
	if (dup2(rfd, lfd) == -1)
		return (-1);
	ft_lstadd(open_fd, ft_lstnew(&rfd, sizeof(int)), 0);
	return (0);
}

char		sh_dless(t_fd *test_fd, t_list **open_fd)
{
	int		lfd;

	lfd = test_fd->io_default ? 0 : sh_check_fd(test_fd->left_str);
	ft_lstadd(open_fd, ft_lstnew(&lfd, sizeof(int)), 0);
	dup2(test_fd->here_doc, lfd);
	close(test_fd->here_doc);
	return (0);
}
