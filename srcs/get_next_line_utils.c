/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: melodiebos <melodiebos@student.le-101.f    +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 17:47:15 by mbos         #+#   ##    ##    #+#       */
/*   Updated: 2019/11/07 17:24:45 by melodiebos  ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (i);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *buffer)
{
	unsigned int	i;
	unsigned int	j;
	char			*join;

	if (s1 == NULL && buffer == NULL)
		return (NULL);
	if (!(join = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(buffer) + 1)))))
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (buffer[j] != '\0' && buffer[j] != '\n')
		join[i++] = buffer[j++];
	join[i] = '\0';
	return (join);
}

t_lst_content	*ft_create_lst_content(char *content)
{
	t_lst_content *new_list;

	if (!(new_list = malloc(sizeof(t_lst_content))))
		return (NULL);
	new_list->content = ft_strjoin(NULL, content); 
	new_list->status = Not_full;
	new_list->next_line = NULL;
	return (new_list);
}

t_lst_fd   *ft_create_lst_fd(t_lst_fd *list, int fd)
{
	t_lst_fd   *new_list;
	
	if (!(new_list = malloc(sizeof(t_lst_fd))))
		return (NULL);
	new_list->list_fd = fd;
	if (!(new_list->first_content = ft_create_lst_content("")))
		return (NULL);
	new_list->next_fd = NULL;
	if (!list)
	{
		new_list->next_fd = NULL;
		return (list = new_list);
	}
	else if (list && fd != list->list_fd)
		list->next_fd = new_list;
	return (new_list);
}

void ft_popout_read_elem(t_lst_content *list_line, t_lst_fd **list_fd)
{
	if (!(list_line) || !(*list_fd))
		return ;
	(*list_fd)->first_content = list_line->next_line;
	if (list_line->content)
	{
		free(list_line->content);
		list_line->content = NULL;
	}
	free(list_line);
	list_line = NULL;
}