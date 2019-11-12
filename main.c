#include "srcs/get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
# include <unistd.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

void	fonction_test_(char *argv)
{
	int li = 1;
	char *line;
	int fd;
	int result = 1;
	fd = open(argv, O_RDONLY);

	printf("fd: %d\n", fd);
	while ((result = get_next_line(fd, &line)) == 1)
	{
		printf(YELLOW "[Return %d]" RESET " - " CYAN "L. %d: " RESET  "%s\n",result, li, line);
		free(line);
		line = NULL;
		li++;
	}
	printf(MAGENTA "[Return %d]" RESET " - " CYAN "L. %d: "  RESET "%s\n",result, li, line);
	free(line);
	line = NULL;
	if (result == -1)
	{
		printf(RED "ERR\n" RESET);
	}
		printf("fd: %d\n", fd);
	while ((result = get_next_line(fd, &line)) == 1)
	{
		printf(YELLOW "[Return %d]" RESET " - " CYAN "L. %d: " RESET  "%s\n",result, li, line);
		free(line);
		line = NULL;
		li++;
	}
	printf(MAGENTA "[Return %d]" RESET " - " CYAN "L. %d: "  RESET "%s\n",result, li, line);
	free(line);
	line = NULL;
	if (result == -1)
	{
		printf(RED "ERR\n" RESET);
	}
	printf("\n\n---------------------\n\n");
}

void	fonction_test_max(char *argv, int max)
{
	int li = 1;
	int result = 1;
	char *line;
	int fd;
	fd = open(argv, O_RDONLY);
	while (result == get_next_line(fd, &line) && li < max)
	{
		printf(YELLOW "[Return %d]" RESET " - " CYAN "L. %d: " RESET  "%s\n",result, li, line);
		li++;
		free(line);
		line = NULL;
	}
}

void 	multiple_files(int fd, char *argv, int max)
{
	int li = 1;
	int result = 0;
	char *line = NULL;


	printf(CYAN "\n\n ## %s ## FD: %d\n\n" RESET, argv, fd);
	while ((result = get_next_line(fd, &line)) && li < max)
	{
		if (result == -1)
		{
			printf(RED "ERR\n" RESET);
			break ;
		}
		printf(YELLOW "[Return %d]" RESET " - " CYAN "L. %d: " RESET  "%s\n",result, li, line);
		free(line);
		line = NULL;
		li++;
	}
	result == 1 ? printf(YELLOW "[Return %d]" RESET, result) : printf(MAGENTA "[Return %d]" RESET, result);
	printf(" - " CYAN "L. %d: " RESET  "%s\n", li, line);
	free(line);
	line = NULL;
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


int     main(int argc, char** argv)
{
	char *line = NULL;
	int result;

	if (argv[1][0] == '0')
	{

		printf(GREEN "\n>> TEST 0 - Printf the entire file <<\n\n" RESET);
		fonction_test_(argv[2]);
	}
	if (argv[1][0] == '1')
	{

		printf(GREEN "\n>> TEST 1 - Printf the 5 first lines <<\n\n" RESET);

		fonction_test_max(argv[2], 70);
	}
	if (argv[1][0] == '2')
	{

		printf(GREEN "\n>>TEST 2 - Open successively argc <<\n\n" RESET);
		fonction_test_multiple_files(argv, argc - 2, 5);
	}
	if (argv[1][0] == '3')
	{

		printf(GREEN "\n>>TEST 3 - FD is corrupt <<\n\n" RESET);
		printf(RED "||  FD = 101  ||\n\n" RESET);
		(result = get_next_line(42, &line)) == -1 ? printf(GREEN " [ %d ] YEAH !" RESET, result) : printf(MAGENTA " [ %d ] " RESET, result);
	}

	printf(YELLOW "\n\n---------------------\n\n" RESET);

	return(0);
}