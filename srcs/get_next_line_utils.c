/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mbos <mbos@student.le-101.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 17:47:15 by mbos         #+#   ##    ##    #+#       */
/*   Updated: 2019/11/09 16:05:32 by mbos        ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

int				ft_strlen(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (i);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

char			*ft_join(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*join;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!(join = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2) + 1)))))
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] != '\0' && s2[j] != '\n')
		join[i++] = s2[j++];
	free(s1);
	s1 = NULL;
	join[i] = '\0';
	return (join);
}

t_lst_line		*ft_create_lst_line(char *line)
{
	t_lst_line *new_lst;

	if (!(new_lst = malloc(sizeof(t_lst_line))))
		return (NULL);
	new_lst->line = ft_join(NULL, line);
	new_lst->status = Not_full;
	new_lst->next_line = NULL;
	return (new_lst);
}

t_lst_fd		*ft_create_lst_fd(t_lst_fd *lst, int fd)
{
	t_lst_fd	*new_lst;

	if (!(new_lst = malloc(sizeof(t_lst_fd))))
		return (NULL);
	new_lst->lst_fd = fd;
	if (!(new_lst->first_line = ft_create_lst_line("")))
		return (NULL);
	new_lst->next_fd = NULL;
	if (!lst)
	{
		new_lst->next_fd = NULL;
		return (lst = new_lst);
	}
	else if (lst && fd != lst->lst_fd)
		lst->next_fd = new_lst;
	return (new_lst);
}

/*
** Delete first elem
** lst_line = lst_fd->first_line
*/

void			ft_popout_read_elem(t_lst_line *lst_line, t_lst_fd **lst_fd)
{
	if (!(lst_line) || !(*lst_fd))
		return ;
	(*lst_fd)->first_line = lst_line->next_line;
	free(lst_line->line);
	lst_line->line = NULL;
	free(lst_line);
	lst_line = NULL;
}
