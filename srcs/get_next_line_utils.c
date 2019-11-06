/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mbos <mbos@student.le-101.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/06 17:47:15 by mbos         #+#   ##    ##    #+#       */
/*   Updated: 2019/11/06 19:04:58 by mbos        ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *buffer)
{
	unsigned int	i;
	unsigned int	j;
	char			*join;

	if (s1 == NULL && buffer == NULL)
		return (NULL);
	if (!(join = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(buffer) + 1)))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (buffer[j] != '\0' && buffer[j] != '\0')
		join[i++] = buffer[j++];
	join[i] = '\0';
	return (join);
}


