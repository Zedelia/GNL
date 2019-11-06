/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: melodiebos <melodiebos@student.le-101.f    +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 10:30:39 by melodiebos   #+#   ##    ##    #+#       */
/*   Updated: 2019/11/06 11:37:35 by melodiebos  ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"


int		get_next_line(int fd, char **line)
{
    static t_lst    *list;
    int             len_read;
    char            *buffer = NULL;

    if (fd > FD_SETSIZE || fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0)
        return (ERR);
    if (!(list))
        ft_create_elem(list,fd);
    ft_manage_fd(fd, list);
    while (list->line_status == 0 && len_read != 0)
    {
        if ((len_read = read(fd, buffer, BUFFER_SIZE)) < 0)
            return (ERR);
        if (!len_read)
            return (END_FILE);
        buffer[len_read] = '\0';
        if (!(list = ft_read_buffer(list, buffer)))
            return (ERR);
    }
    if (!list->next_line)
        ft_create_elem(list, fd);
    ft_pop


}