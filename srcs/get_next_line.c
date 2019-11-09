/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mbos <mbos@student.le-101.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 10:30:39 by melodiebos   #+#   ##    ##    #+#       */
/*   Updated: 2019/11/09 15:49:12 by mbos        ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"


int				ft_lstclear(t_lst_fd *lst)
{
	t_lst_fd   *tmp;

	if (!lst)
		return (ERR) ;
	while (lst)
	{
		tmp = lst->next_fd;
		while (lst->first_line)
			ft_popout_read_elem(lst->first_line, &lst);
		free(lst);
		lst = NULL,
		lst = tmp;
	}
	return (ERR);
}

int				ft_alloc_line(t_lst_line **lst_tmp, char *buff, int len_read)
{
	int 	bcursor;
	int		start;

	start = 0;
	bcursor = 0;
	while (buff[bcursor])
	{
		if (buff[bcursor] == '\n')
		{
			if (!((*lst_tmp)->line = ft_join((*lst_tmp)->line, &buff[start])))
				return (0);
		start = bcursor + 1;
		(*lst_tmp)->status = Full_line;
		(*lst_tmp)->next_line = ft_create_lst_line("");
		(*lst_tmp) = (*lst_tmp)->next_line;
		}
		if (bcursor == len_read - 1)
			(*lst_tmp)->line = ft_join((*lst_tmp)->line, &buff[start]);
		bcursor += 1;
		}
	return(1);
}

t_lst_line	*ft_read_buff(t_lst_line *lst, int fd)
{

	int				len_read;
	char	*buff;
	t_lst_line 	*lst_tmp;
	
	lst_tmp = lst;
	while (lst->status != Full_line)
	{
		if (!(buff = malloc(sizeof(char) * (buff_SIZE + 1))))
			return (NULL);
		len_read = read(fd, buff, buff_SIZE);
		buff[len_read] = '\0';
		if (!(ft_alloc_line(&lst_tmp, buff, len_read)))
			return (NULL);
		free(buff);
		buff = NULL;
		if (len_read == 0)
		{
			lst->status = End_file;
			if (!(lst->next_line = ft_create_lst_line("")))
				return (NULL);
			return (lst);
		}
	}
	return (lst);
}

t_lst_fd   		*ft_manage_fd(int fd, t_lst_fd **lst)
{
	t_lst_fd   *lst_tmp;

	lst_tmp = *lst;
	while (lst_tmp->next_fd && lst_tmp->lst_fd != fd)
		lst_tmp = lst_tmp->next_fd;
	if (fd == lst_tmp->lst_fd)
		return (lst_tmp);
	else if (fd != lst_tmp->lst_fd)
		lst_tmp->next_fd = ft_create_lst_fd(lst_tmp, fd);
	return (lst_tmp->next_fd);
}

int				get_next_line(int fd, char **line)
{
	static t_lst_fd		*lst_s;
	t_lst_fd   			*lst_fd;
	t_lst_line   	*lst_line;
	int					result;

	*line = NULL;
	if (!lst_s && !(lst_s = ft_create_lst_fd(lst_s, fd)))
		return (ERR);
	if (fd > FD_SETSIZE || fd < 0 || buff_SIZE < 1 || read(fd, NULL, 0) < 0 
		|| !(lst_fd = ft_manage_fd(fd, &lst_s)))
		return (ft_lstclear(lst_s));
	lst_line = lst_fd->first_line;
	if (!(lst_line = ft_read_buff(lst_fd->first_line, fd))
		|| (!(*line = ft_join(NULL, lst_line->line))))
		return (ft_lstclear(lst_s));
	result = lst_line->status;
	ft_popout_read_elem(lst_fd->first_line, &lst_fd);
	

	return (result);
}
