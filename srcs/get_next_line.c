/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mbos <mbos@student.le-101.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 10:30:39 by melodiebos   #+#   ##    ##    #+#       */
/*   Updated: 2019/11/06 21:18:42 by mbos        ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

t_lst_fd   *ft_manage_fd(int fd, t_lst_fd *list)
{
	t_lst_fd   *list_tmp;

	list_tmp = list;
	while (list_tmp && list_tmp->list_fd != fd)
		list_tmp = list_tmp->next_fd;
	if (list_tmp && fd == list_tmp->list_fd)
		return (list_tmp);
	return (ft_create_lst_fd(list_tmp, fd));
}

int		alloc_content(t_lst_content **list_tmp, char *buffer)
{
	int 	bcursor;

	bcursor = 0;
	while (buffer[bcursor])
	{
		if (buffer[bcursor] == '\n')
		{
			if (!((*list_tmp)->content = ft_strjoin((*list_tmp)->content, buffer)))
				return (0);
		(*list_tmp)->status = Full_line;
		(*list_tmp)->next_line = ft_create_lst_content(NULL);
		(*list_tmp) = (*list_tmp)->next_line;
		}
		bcursor += 1;
	}
	return(1);
}


t_lst_content	*ft_read_buffer(t_lst_content *list, int fd)
{

	int				len_read;
	char			buffer[BUFFER_SIZE + 1];
	t_lst_content 	*list_tmp;
	
	list_tmp = list;
	while (list->status != Full_line)
	{
		len_read = read(fd, buffer, BUFFER_SIZE);
		if (len_read == 0)
		{
			list->status = End_file;
			return (list);
		}
		buffer[len_read] = '\0';
		if (!(alloc_content(&list_tmp, buffer)))
			return (NULL);
	}
	return (list);
}


int		get_next_line(int fd, char **line)
{
	static t_lst_fd		*list_s;
	t_lst_fd   			*list_fd;
	t_lst_content   	*list_line;

	list_fd = list_s;
	if (fd > FD_SETSIZE || fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0 ||
		!(list_fd = ft_manage_fd(fd, list_s)))
		return (ERR);
	list_fd->first_content = list_line;
	list_line = ft_read_buffer(list_fd->first_content, fd);

	*line = ft_strjoin(*line, list_line->content);


	list = ft_pop_out_elem(list);
	return (END_FILE);
}
