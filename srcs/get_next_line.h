/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: melodiebos <melodiebos@student.le-101.f    +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/29 09:46:01 by mbos         #+#   ##    ##    #+#       */
/*   Updated: 2019/11/06 10:38:08 by melodiebos  ###    #+. /#+    ###.fr     */
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
#  define BUFFER_SIZE 1
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
	Not_full = 0,
	Full = 1,
}						t_line_status;

typedef struct			s_lst {
	int					line_fd;
	char				*line_content;
	t_line_status		line_status;
	struct s_lst		*next_line;
	struct s_lst		*next_fd;
}						t_lst;

int						get_next_line(int fd, char **line);
#endif
