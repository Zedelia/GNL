/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mbos <mbos@student.le-101.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/29 09:46:01 by mbos         #+#   ##    ##    #+#       */
/*   Updated: 2019/11/12 14:32:31 by mbos        ###    #+. /#+    ###.fr     */
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
	Line_read = 3,
}						t_line_status;

typedef struct			s_lst_fd {
	int						lst_fd;
	struct s_lst_line		*first_line;
	struct s_lst_fd			*next_fd;

}						t_lst_fd;

typedef struct			s_lst_line {
	char					*line;
	t_line_status			status;
	struct s_lst_line		*next_line;
}						t_lst_line;

int						get_next_line(int fd, char **line);
char					*ft_join(char *s1, char *buff);
int						ft_strlen(char *str);
t_lst_line				*ft_create_lst_line(char *line);
t_lst_fd				*ft_create_lst_fd(t_lst_fd *lst, int fd);
void					ft_popout_read_elem(t_lst_line *lst_line,
													t_lst_fd **lst_fd);
int						ft_lstclear(t_lst_fd *lst);

#endif
