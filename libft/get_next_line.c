/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:10:34 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/01 17:17:47 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*print_line(char *stash)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\n')
		i++;
	line = (char *)malloc(i + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, stash, i);
	return (line);
}

char	*clean_stash(char *stash)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	i++;
	new = (char *)malloc(ft_strlen(stash + i) + 1);
	if (!new)
		return (free(stash), NULL);
	while (stash[i])
		new[j++] = stash[i++];
	new[j] = '\0';
	free(stash);
	return (new);
}

void	*ft_edge_cases(int fd, char *stash, ssize_t *read_bytes)
{
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	*read_bytes = 1;
	return (stash);
}

char	*strjoin_free(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = 0;
	s3 = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s3 == NULL)
		return (free(s1), NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	free(s1);
	return (s3);
}

char	*get_next_line(int fd)
{
	ssize_t		read_bytes;
	char		buffer[BUFFER_SIZE + 1];
	static char	*stash;
	char		*line;

	stash = ft_edge_cases(fd, stash, &read_bytes);
	if (!stash)
		return (NULL);
	while (!ft_strchr(stash, '\n') && (read_bytes > 0))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes > 0)
		{
			buffer[read_bytes] = '\0';
			stash = strjoin_free(stash, buffer);
			if (!stash)
				return (NULL);
		}
	}
	if (read_bytes == -1)
		return (free(stash), NULL);
	line = print_line(stash);
	stash = clean_stash(stash);
	stash = free_stash_if_line_null(stash, line);
	return (line);
}
