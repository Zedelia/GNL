/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mbos <mbos@student.le-101.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 10:30:39 by melodiebos   #+#   ##    ##    #+#       */
/*   Updated: 2019/11/09 15:05:28 by mbos        ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"


int		ft_lstclear(t_lst_fd *list)
{
	t_lst_fd   *tmp;

	if (!list)
		return (ERR) ;
	while (list)
	{
		tmp = list->next_fd;
		while (list->first_content)
			ft_popout_read_elem(list->first_content, &list);
		free(list);
		list = NULL,
		list = tmp;
	}
	return (ERR);
}

int		ft_alloc_content(t_lst_content **list_tmp, char *buffer, int len_read)
{
	int 	bcursor;
	int		start_line;

	start_line = 0;
	bcursor = 0;
	while (buffer[bcursor])
	{
		if (buffer[bcursor] == '\n')
		{
			if (!((*list_tmp)->content = ft_strjoin((*list_tmp)->content, &buffer[start_line])))
				return (0);
		start_line = bcursor + 1;
		(*list_tmp)->status = Full_line;
		(*list_tmp)->next_line = ft_create_lst_content("");
		(*list_tmp) = (*list_tmp)->next_line;
		}
		if (bcursor == len_read - 1)
			(*list_tmp)->content = ft_strjoin((*list_tmp)->content, &buffer[start_line]);
		bcursor += 1;
		}
	return(1);
}

t_lst_content	*ft_read_buffer(t_lst_content *list, int fd)
{

	int				len_read;
	char	*buffer;
	t_lst_content 	*list_tmp;
	
	list_tmp = list;
	while (list->status != Full_line)
	{
		if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (NULL);
		len_read = read(fd, buffer, BUFFER_SIZE);
		buffer[len_read] = '\0';
		if (!(ft_alloc_content(&list_tmp, buffer, len_read)))
			return (NULL);
		free(buffer);
		buffer = NULL;
		if (len_read == 0)
		{
			list->status = End_file;
			if (!(list->next_line = ft_create_lst_content("")))
				return (NULL);
			return (list);
		}
	}
	return (list);
}

t_lst_fd   *ft_manage_fd(int fd, t_lst_fd **list)
{
	t_lst_fd   *list_tmp;

	list_tmp = *list;
	while (list_tmp->next_fd && list_tmp->list_fd != fd)
		list_tmp = list_tmp->next_fd;
	if (fd == list_tmp->list_fd)
		return (list_tmp);
	else if (fd != list_tmp->list_fd)
		list_tmp->next_fd = ft_create_lst_fd(list_tmp, fd);
	return (list_tmp->next_fd);
}

int		get_next_line(int fd, char **line)
{
	static t_lst_fd		*list_s;
	t_lst_fd   			*list_fd;
	t_lst_content   	*list_line;
	int					result;

	*line = NULL;
	if (!list_s && !(list_s = ft_create_lst_fd(list_s, fd)))
		return (ERR);
	if (fd > FD_SETSIZE || fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0 
		|| !(list_fd = ft_manage_fd(fd, &list_s)))
		return (ft_lstclear(list_s));
	list_line = list_fd->first_content;
	if (!(list_line = ft_read_buffer(list_fd->first_content, fd))
		|| (!(*line = ft_strjoin(NULL, list_line->content))))
		return (ft_lstclear(list_s));
	result = list_line->status;
	ft_popout_read_elem(list_line, &list_fd);
	if (!list_fd->first_content->content)
		ft_popout_read_elem(list_fd->first_content, &list_fd);
	// printf(">> %p\n", list_fd->first_content->content);
	// printf(">> %p\n", list_fd->first_content->next_line);
	return (result);
}
