/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tcensier <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/12 12:09:22 by tcensier      #+#    #+#                 */
/*   Updated: 2022/12/12 14:52:28 by tcensier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 64
#endif

static ssize_t	ft_strchr(char *str, char c)
{
	ssize_t	index;

	if (!str)
		return (-1);
	index = 0;
	while (str[index])
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

static char	*trim_line(char *line, char *saved_buffer)
{
	ssize_t	index_nl;
	char	*heap_ptr;

	index_nl = ft_strchr(line, '\n');
	if (index_nl != -1)
	{
		ft_strlcpy(saved_buffer, line + index_nl + 1, BUFFER_SIZE + 1);
		heap_ptr = line;
		line = (char *)malloc(sizeof(char) * index_nl + 2);
		if (!line)
			return (free(heap_ptr), NULL);
		ft_strlcpy(line, heap_ptr, index_nl + 2);
		free(heap_ptr);
	}
	else
		saved_buffer[0] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	saved_buffer[BUFFER_SIZE + 1];
	char		buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*heap_ptr;
	ssize_t		read_position;

	line = ft_strdup(saved_buffer);
	//line = NULL;
	if (!line)
		return (NULL);
	while (ft_strchr(line, '\n') == -1)
	{
		read_position = read(fd, buffer, BUFFER_SIZE);
		if (read_position <= 0)
			break ;
		buffer[read_position] = '\0';
		heap_ptr = line;
		line = ft_strjoin(line, buffer);
		//line = NULL;
		if (!line)
			return (free(heap_ptr), NULL);
		free(heap_ptr);
	}
	if (line[0] == '\0' || read_position == -1)
	{
		saved_buffer[0] = '\0';
		return (free(line), NULL);
	}
	line = trim_line(line, saved_buffer);
	return (line);
}

/*
int main(void)
{
	int fd = open("input.txt", O_RDONLY);
	int i = 0;
	char *line;

	while (i < 10)
	{
		line = get_next_line(fd);
		printf("%s", line);
		printf("\n_________________\n");
		free(line);
		i++;
	}
	close(fd);
	return (0);
}
*/
