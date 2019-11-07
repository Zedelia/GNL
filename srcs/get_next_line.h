/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: melodiebos <melodiebos@student.le-101.f    +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/29 09:46:01 by mbos         #+#   ##    ##    #+#       */
/*   Updated: 2019/11/07 15:34:10 by melodiebos  ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# define BUFFER_IS_FULL(bcursor) (bcursor == BUFFER_SIZE - 1) ? 1 : 0

typedef enum			e_result
{
	ERR = -1,
	END_FILE = 0,
	LINE_OK = 1
}						t_result;


typedef	enum			e_line_status
{
	Not_full = 2,
	End_file = 0,
	Full_line = 1,
}						t_line_status;

typedef struct					s_lst_fd {
	int							list_fd;
	struct s_lst_content		*first_content;
	struct s_lst_fd				*next_fd;
}								t_lst_fd;

typedef struct					s_lst_content {
	char						*content;
	t_line_status				status;
	struct s_lst_content		*next_line;
}								t_lst_content;

int				get_next_line(int fd, char **line);
char			*ft_strjoin(char *s1, char *buffer);
int				ft_strlen(char *str);
t_lst_content	*ft_create_lst_content(char *content);
t_lst_fd 		 *ft_create_lst_fd(t_lst_fd *list, int fd);
void ft_popout_read_elem(t_lst_content *list_line, t_lst_fd **list_fd);

#endif
