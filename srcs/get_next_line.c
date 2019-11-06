/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mbos <mbos@student.le-101.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 10:30:39 by melodiebos   #+#   ##    ##    #+#       */
/*   Updated: 2019/11/06 19:19:11 by mbos        ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

t_lst   *ft_create_elem(t_lst *list, int fd)
{
	t_lst   *new_list;
	
	if (!(new_list = malloc(sizeof(t_lst))))
		return (NULL);
	new_list->line_fd = fd;
	new_list->line_content = NULL;
	new_list->next_line = NULL;
	new_list->line_status = Not_full;
	if (!list)
	{
		new_list->next_fd = NULL;
		return (list = new_list);
	}
	else if (list && fd == list->line_fd)
		new_list->next_fd = list->next_fd;
	else if (list && fd != list->line_fd)
		list->next_fd = new_list;
	return (new_list);
}

t_lst   *ft_manage_fd(int fd, t_lst *list)
{
	t_lst   *list_tmp;

	list_tmp = list;
	while (list_tmp && list_tmp->line_fd != fd)
		list_tmp = list_tmp->next_fd;
	if (list_tmp && fd == list_tmp->line_fd)
		return (list_tmp);
	return (ft_create_elem(list_tmp, fd));
}

t_lst	*ft_read_buffer(t_lst *list, char *buffer, int len_read, char **line)
{
	int		bcursor;
	int		start_line;

	start_line = 0;
	bcursor = 0;
	while (buffer[bcursor])
	{
		if (buffer[bcursor] == '\n')
		{
			if (!(*line = ft_strjoin(list->line_content, buffer)))
				return (NULL);
			start_line = bcursor;
			list->line_content = ft_strdup(&buffer[bcursor]);
		}

		bcursor+= 1;
	}
	return (list);
}


int		get_next_line(int fd, char **line)
{
	static t_lst    *list;
	t_lst           *list_tmp;
	int             len_read;
	char            buffer[BUFFER_SIZE];

	if (fd > FD_SETSIZE || fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0 ||
		!(list_tmp = ft_manage_fd(fd, list)))
		return (ERR);
	while (list->line_status == 0 && len_read != 0)
	{
		if ((len_read = read(fd, buffer, BUFFER_SIZE)) < 0)
			return (ERR);
		if (!len_read)
			return (END_FILE);
		buffer[len_read] = '\0';
		if (!(list = ft_read_buffer(list, buffer, len_read, line)))
			return (ERR);
	}
	if (!list->next_line)
		ft_create_elem(list, fd);
	list = ft_pop_out_elem(list);
	return (END_FILE);
}
