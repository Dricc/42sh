/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:00:54 by bviala            #+#    #+#             */
/*   Updated: 2017/11/08 19:05:50 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

# include "libft.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_ldl
{
	void			*content;
	struct s_ldl	*next;
	struct s_ldl	*prev;
}					t_ldl;

void				ft_lstrev(t_list **liste);
void				ft_lstprint(t_list **list);
void				ft_lstprint_name(t_list **list);
void				ft_lstclear(t_list **liste);
size_t				ft_lstsize(t_list *begin_list);
void				ft_lstaddback(t_list **alst, t_list *new);
void				ft_lstadd(t_list **alst, t_list *new, int index);
void				ft_lstiter(t_list *lst, void (*f) (t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f) (t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdel(t_list **alst, void (*del) (void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del) (void *, size_t));
t_list				*ft_lstswap(t_list *list);
void				ft_lstsort(t_list **begin_list, int (*cmp)());

t_ldl				*ft_ldl_back(t_ldl *ldl);
void				ft_ldl_clear(t_ldl **ldl, void (*del)());
void				ft_ldl_del(t_ldl **ldl, void (*del)());
t_ldl				*ft_ldl_front(t_ldl *ldl);
void				ft_ldl_new(t_ldl **ldl, void *content);
void				ft_ldl_pushback(t_ldl **ldl, void *content);
void				ft_ldl_pushfront(t_ldl **ldl, void *content);
void				ft_ldl_revers(t_ldl **ldl);
size_t				ft_ldl_size(t_ldl *ldl);
#endif
