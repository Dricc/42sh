/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 18:10:03 by bviala            #+#    #+#             */
/*   Updated: 2017/11/21 18:13:00 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include <sys/stat.h>
# include <sys/types.h>

# define BUFF_SIZE 50
# define CT(Pointeur) ((t_str*)(Pointeur->content))

typedef struct		s_str
{
	int				fd;
	char			*buff;
	int				size;
}					t_str;

int					ft_islower(int c);
int					ft_isalpha(int n);
int					ft_isdigit(int n);
int					ft_isalnum(int n);
int					ft_isascii(int n);
int					ft_isprint(int n);
int					ft_isspace(int c);
int					ft_is_a_dir(const char *path);
int					ft_is_a_file(const char *path);
int					ft_is_a_reg_file(const char *path);
int					ft_toupper(int n);
int					ft_tolower(int n);
int					ft_isupper(int nb);
void				ft_swap(void **a, void **b);
void				ft_sort_wordtab(char **tab);
void				ft_rev_wordtab(char **tab);
int					get_next_line(const int fd, char **line);
void				ft_error(char *str, void (*f)(void));
int					ft_iswcntrl(unsigned int c);

#endif
