#include "srcs/get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
# include <unistd.h>

#define SUCCESS printf("\033[32m")
#define FAILED printf("\033[31m")
#define NORMAL printf("\033[0m");
#define UNKNOWN printf("\033[33m")
/*
void	fonction_test_(char *argv)
{
	int i = 0;
	int rslt=0;
	char *line;
	int fd;
	int result;
	fd = open(argv, O_RDONLY);
	NORMAL;
	while ((result = get_next_line(fd, &line)) == 1)
	{
		printf("gnl: %d - L. %d - %s\n", rslt, i, line);
		i++;
	}
	if (get_next_line(fd, &line) == 0)
	{
		NORMAL;
		printf("EOF\n");
	}
	if (result == -1)
	{
		UNKNOWN;
		printf("ERR\n");
	}
	NORMAL;
	printf("\n\n---------------------\n\n");
}

void	fonction_test_max(char *argv, int max)
{
	int i = 0;
	int j = 0;
	char *line;
	int fd;
	fd = open(argv, O_RDONLY);
	while ((j = get_next_line(fd, &line)) && i < max)
	{
		printf("L. %d - %s\n", i, line);
		i++;
	}
}

void 	multiple_files(int fd, char *argv, int max)
{
	int li = 0;
	int result = 0;
	char *line = NULL;


	printf("\n%s - fd : %d\n", argv, fd);
	while ((result = get_next_line(fd, &line)) && li < max)
	{
		if (result == -1)
		{
			UNKNOWN;
			printf("ERR\n");
			break ;
		}
		printf("L. %d - %s\n", li, line);
		free(line);
		line = NULL;
		li++;
	}
}

void	fonction_test_multiple_files(char **argv, int argc, int max)
{
	int i = 0;
	int loop = 1;
	int fd[argc];

	while (i < argc)
	{
		fd[i] = open(argv[i + 2], O_RDONLY);
		if (fd[i] < 0)
		{
			FAILED;
			printf("fd ERR");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < argc && loop < max)
	{
		multiple_files(fd[i], argv[i + 2], max);
		i++;
		if (i == argc)
		{
			loop++;
			i = 0;
		}
	}
}
*/
size_t		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}


char	*ft_strdup(const char *s1)
{
	int		len_s1;
	int		i;
	char	*cpy;

	i = 0;
	len_s1 = ft_strlen(s1);
	if (!(cpy = malloc((len_s1 + 1) * sizeof(char))))
		return (NULL);
	while (i < len_s1)
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

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
        return (new_list);
    }
    else if (list && fd == list->line_fd)
	{
        new_list->next_fd = list->next_fd;
		list->next_line = new_list;
	}
	else if (list && fd != list->line_fd)
        list->next_fd = new_list;
    return (list);
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


int     main(int argc, char** argv)
{
	int len_read;
	char buffer[201];
	int fd;
	char *arg = argv[1];
	int i = 0;
	t_lst *list = NULL;
	t_lst *list_tmp = NULL;
	t_lst *list_tmp_tmp = NULL;
	t_lst *list_tmp_tmp_tmp = NULL;


	fd = open(arg, O_RDONLY);


	list = ft_create_elem(list, fd);
	len_read = read(fd, buffer, 100);
	buffer[len_read] = 0;
	list->line_content = ft_strdup(buffer);
	printf("fd = %d \nlen_read = %d  \n", fd, len_read);
	while (buffer[i])
	{
		buffer[i] = 0;
		i++;
	}



	buffer[len_read] = 0;
	

	// if (argv[1][0] == '0')
	// {
	// 	UNKNOWN;
	// 	printf("\nTEST 0 - Printf the entire file\n");
	// 	NORMAL;
	// 	fonction_test_(argv[2]);
	// 	printf("\n\n---------------------\n\n");
	// }
	// if (argv[1][0] == '1')
	// {
	// 	UNKNOWN;
	// 	printf("\nTEST 1 - Printf the 5 first lines\n");
	// 	NORMAL;
	// 	fonction_test_max(argv[2], 5);
	// 	printf("\n\n---------------------\n\n");
	// }
	// if (argv[1][0] == '2')
	// {
	// 	UNKNOWN;
	// 	printf("\nTEST 2 - Open successively argc\n");
	// 	NORMAL;
	// 	fonction_test_multiple_files(argv, argc - 2, 4);
	// 	printf("\n\n---------------------\n\n");
	// }

	return(0);
}