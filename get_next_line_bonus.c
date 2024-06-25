/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbailly <pbailly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:03:09 by alibaba           #+#    #+#             */
/*   Updated: 2024/06/25 10:31:18 by pbailly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*fill(int fd, char *left_src, char *buff)
{
	ssize_t	b_read;
	char	*temp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buff, BUFFER_SIZE);
		if (b_read == -1)
			return (free(left_src), NULL);
		else if (b_read == 0)
			break ;
		buff[b_read] = '\0';
		if (!left_src)
			left_src = ft_strdup("");
		temp = left_src;
		if (temp != NULL && buff != NULL)
			left_src = ft_strjoin(temp, buff);
		free(temp);
		temp = NULL;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (left_src);
}

static char	*set_line(char *line)
{
	char	*left_src;
	ssize_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == 0 || line[i + 1] == 0)
		return (NULL);
	left_src = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*left_src == 0)
	{
		free(left_src);
		left_src = NULL;
	}
	line[i + 1] = '\0';
	return (left_src);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*line;
	static char	*left_src[4096];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(left_src[fd]);
		left_src[fd] = NULL;
		return (NULL);
	}
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	line = fill(fd, left_src[fd], buff);
	free(buff);
	buff = NULL;
	if (!line)
	{
		left_src[fd] = NULL;
		return (NULL);
	}
	left_src[fd] = set_line(line);
	return (line);
}

/* #include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	char	*line1;
	char	*line2;
	int		fd;
	int		fd2;
	int		i;

	line1 = NULL;
	line2 = NULL;
	fd = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	i = 0;
	while (i++ < 1)
	{
		line1 = get_next_line(fd);
		line2 = get_next_line(fd2);
		printf("%s:%s\n", line1, line2);
		free(line1);
		free(line2);
	}
	close(fd);
	close(fd2);
} */
