/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:47:04 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/05 14:00:01 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/* this functions mimics the heredoc command
	- we run an infinite loop and read each line of the file until 
the limiter is found: we have to if statements:
1- if limiter is read, break the loop and return the lines read
2- if limiter not yet found, we feed into a custum realloc function a new size
each time and concatenate the line buffer (current_line) into our final lines
which gets returned as when limiter is then found
*/
char	**here_doc_reader(char *limiter)
{
	t_vars	p;
	t_pipex ptr;

	p.lines = NULL;
	p.up_line = NULL;
	ptr.lines_received = NULL;
	p.t_len = 0;
	while (1)
	{
		p.up_line = get_next_line(0);
		if (!p.up_line || ft_strncmp(p.up_line, limiter, ft_strlen(limiter)) == 0)
		{
			free(p.up_line);
			break ;
		}
		else
		{
			p.new_size = p.t_len + ft_strlen(p.up_line) + 1;
			p.lines = ft_realloc(p.lines, p.t_len + 1, p.new_size);
			if (!p.lines)
				return (NULL);
			ft_strlcpy(p.lines + p.t_len, p.up_line, ft_strlen(p.up_line) + 1);
			p.t_len += ft_strlen(p.up_line);
			free(p.up_line);
		}
	}
	ptr.lines_received = ft_split(p.lines, '\n');
	if (!ptr.lines_received)
		return (free(p.lines), NULL);
	free(p.lines);
	return (ptr.lines_received);
}

void	execute_here_doc(char **av, int argc, char **envp)
{
	char	*limiter;
	char	**output;
	int		tmp_fd;
	t_pipex	parsed;

	limiter = av[2];
	tmp_fd = open("temp_file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (tmp_fd < 0)
		safe_exit("Error opening file\n");
	output = here_doc_reader(limiter);
	if (!output)
		safe_exit("Error readin here_doc\n");
	for (size_t i = 0; output[i]; i++)
	{
   		write(tmp_fd, output[i], ft_strlen(output[i]));
    	write(tmp_fd, "\n", 1);
	}
	//write(tmp_fd, output, array_len(output));
	free_split(output);
	close(tmp_fd);
	parsed = normal_parsing(argc, av, envp, 3);
	parsed.infile = open("temp_file.txt", O_RDONLY);
	if (parsed.infile < 0)
		safe_exit("Error opening temp file\n");
	execute(parsed.cmds, argc, av, parsed.cmd_count);
	close(parsed.infile);
	unlink("temp_file.txt");
}
