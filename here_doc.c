/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:47:04 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/10 12:22:52 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*here_doc_reader(char *limiter)
{
	t_vars	p;

	p.buffer = ft_strdup("");
	if (!p.buffer)
		return (NULL);
	while (1)
	{
		p.lines = get_next_line(0);
		if (!p.lines || is_limiter(p.lines, limiter))
			return (free(p.lines), p.buffer);
		p.len = ft_strlen(p.buffer);
		p.new_len = p.len + ft_strlen(p.lines) + 1;
		p.buffer = ft_realloc(p.buffer, p.len, p.new_len + 1);
		if (!p.buffer)
			return (free(p.lines), free(p.buffer), NULL);
		ft_strcat(p.buffer, p.lines);
		ft_strcat(p.buffer, "\n");
		free(p.lines);
	}
	return (p.buffer);
}

void	execute_here_doc(char **av, int argc, char **envp)
{
	char	*limiter;
	char	*output;
	int		tmp_fd;
	t_pipex	*p;

	limiter = av[2];
	tmp_fd = open("temporary.txt", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (tmp_fd < 0)
		exit(1);
	output = here_doc_reader(limiter);
	if (!output)
		safe_exit("Error readin here_doc\n");
	write(tmp_fd, output, ft_strlen(output));
	free(output);
	close(tmp_fd);
	p = normal_parsing(argc, av, envp, 3);
	if (!p)
		safe_exit("Parsing failed\n");
	p->infile = open("temp_file.txt", O_RDONLY);
	if (p->infile < 0)
		exit(1);
	execute(p->cmds, argc, av, p->cmd_count);
	close(p->infile);
	unlink("temp_file.txt");
	free_pipex(p);
}
