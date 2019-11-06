/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mbos <mbos@student.le-101.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 17:47:15 by mbos         #+#   ##    ##    #+#       */
/*   Updated: 2019/11/06 21:18:43 by mbos        ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
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
	while (s1[i])
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
	if (!content)
		new_list->content = NULL;
	else
		new_list->content = content;
	new_list->next_line = NULL;
	return (new_list);
}

t_lst_fd   *ft_create_lst_fd(t_lst_fd *list, int fd)
{
	t_lst_fd   *new_list;
	
	if (!(new_list = malloc(sizeof(t_lst_fd))))
		return (NULL);
	new_list->list_fd = fd;
	if (!(new_list->first_content = ft_create_lst_content(0)))
		return (NULL);
	if (!list)
	{
		new_list->next_fd = NULL;
		return (list = new_list);
	}
	else if (list && fd != list->list_fd)
		list->next_fd = new_list;
	return (new_list);
}
