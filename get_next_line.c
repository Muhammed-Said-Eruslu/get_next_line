/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mueruslu <mueruslu@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 16:56:52 by mueruslu          #+#    #+#             */
/*   Updated: 2026/02/18 16:41:28 by mueruslu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_all(char *stash, char *buffer)
{
	free(buffer);
	free(stash);
	return (NULL);
}

static char	*ft_read_and_stash(int fd, char *stash)
{
	char	*buffer;
	int		byte_reads;

	if (!stash)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	byte_reads = 1;
	while (!ft_strchr(stash, '\n') && byte_reads != 0)
	{
		byte_reads = read(fd, buffer, BUFFER_SIZE);
		if (byte_reads == -1)
			return (free_all(stash, buffer));
		buffer[byte_reads] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

static char	*ft_extract_line(char *stash)
{
	char	*new_str;
	int		i;

	i = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		new_str = malloc(sizeof(char) * (i + 2));
	else
		new_str = malloc(sizeof(char) * (i + 1));
	if (!new_str)
		return (NULL);
	i = -1;
	while (stash[++i] && stash[i] != '\n')
		new_str[i] = stash[i];
	if (stash[i] == '\n')
		new_str[i++] = '\n';
	new_str[i] = '\0';
	return (new_str);
}

static char	*ft_clean_stash(char *stash)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_str = malloc(sizeof(char) * (ft_strlen(stash) - i));
	if (!new_str)
	{
		free (stash);
		return (NULL);
	}
	i++;
	j = 0;
	while (stash[i])
		new_str[j++] = stash[i++];
	new_str[j] = '\0';
	free(stash);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_extract_line(stash);
	if (!line || line[0] == '\0')
	{
		free(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	stash = ft_clean_stash(stash);
	return (line);
}
