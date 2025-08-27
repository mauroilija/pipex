/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:47:04 by milija-h          #+#    #+#             */
/*   Updated: 2025/08/27 10:42:57 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/* this functions mimics the heredoc command
    - we run an infinite loop and read each line of the file until 
the limiter is found: we have to if statements:
1- if limiter is read, break the loop and return the lines read
2- if limiter not yet found, we feed into a custum realloc function a new size
each time and concatenate the line buffer (current_line) into our final lines, which
gets returned as when limiter is then found
*/
char    *here_doc_reader(char *limiter) // im a bit lost not gonna lie
{
    char    *lines; // will return all in between heredoc and limiter
    char    *current_line; // receives lines slowly as we read
    size_t  total_len; //both total len and new_size update each call
    size_t  new_size; // and passed down to realloc so our buffer grows dynamically

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
            lines = ft_realloc(lines, total_len + 1, new_size);
            if (!lines)
                return (NULL);
            ft_strlcat(lines, current_line, new_size);
            total_len += ft_strlen(current_line);
            free(current_line);
        }
    }
    return (lines);
}
