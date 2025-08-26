/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:47:04 by milija-h          #+#    #+#             */
/*   Updated: 2025/08/26 17:20:28 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *here_doc_reader(char *limiter) // im a bit lost not gonna lie
{
    t_pipex p;
    char    *lines;
    char    *current_line;
    size_t  total_len;
    size_t  new_size;

    lines = NULL;
    current_line = NULL;
    total_len = 0;
    while (1)
    {
        current_line = get_next_line(0);
        if (!current_line)
            break ;
        if (ft_strncmp(current_line, limiter, ft_strlen(limiter)) == 0
            && current_line[ft_strlen(limiter)] == '\n')
        {
            free(current_line);
            break;
        }
        else
        {
            new_size = total_len + ft_strlen(current_line) + 1;
            lines = ft_realloc(lines, BUFFER_SIZE + 1, new_size);
            if (!lines)
                return (NULL);
            ft_strlcat(lines, current_line, new_size);
            total_len += ft_strlen(current_line);
            free(current_line);
        }
    }
    return (lines);
}
