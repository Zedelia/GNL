/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: melodiebos <melodiebos@student.le-101.f    +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 10:30:39 by melodiebos   #+#   ##    ##    #+#       */
/*   Updated: 2019/11/07 17:20:12 by melodiebos  ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"


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
		(*list_tmp)->next_line = ft_create_lst_content(NULL);
		(*list_tmp) = (*list_tmp)->next_line;
		}
		if (bcursor == len_read - 1)
		{
			(*list_tmp)->content = ft_strjoin((*list_tmp)->content, &buffer[start_line]);
		}
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
		if (len_read == 0)
		{
			list->status = End_file;
			if (!(list->next_line = ft_create_lst_content("")))
				return (NULL);
			return (list);
		}
		free(buffer);
		buffer = NULL;
	}
	return (list);
}

t_lst_fd   *ft_manage_fd(int fd, t_lst_fd **list)
{
	t_lst_fd   *list_tmp;

	list_tmp = *list;
	while (list_tmp->next_fd && list_tmp->list_fd != fd)
		list_tmp = list_tmp->next_fd;
	if (list_tmp && fd == list_tmp->list_fd)
		return (list_tmp);
	else if (list_tmp && fd != list_tmp->list_fd)
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
		return (ERR);
	list_line = list_fd->first_content;
	if (!(list_line = ft_read_buffer(list_fd->first_content, fd)))
		return (ERR);
	if (!(*line = ft_strjoin(*line, list_line->content)))
		return (ERR);
	result = list_line->status;
	ft_popout_read_elem(list_line, &list_fd);
	return (result);
}
