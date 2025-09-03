/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:19:46 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/03 20:31:15 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// checck for exit codes
//this functions execute all the necessary commands
void	execute(t_cmd *cmds, int argc, char **av, int cmd_count)
{
	t_pipex	p;
	int		prev_pipe;
	int		next_pipe;
	pid_t	child_pid;

	if (argc > 1 && ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		p.infile = open("temp_file.txt", O_RDONLY);
		if (p.infile < 0)
			safe_exit("Error opening infile0\n");
		p.outfile = open(av[argc -1], O_CREAT | O_WRONLY | O_APPEND, 0664);
		if (p.outfile < 0)
			safe_exit("Error opening outfile\n");
	}
	else
	{
		p.infile = open(av[1], O_RDONLY);
		if (p.infile < 0)
			safe_exit("Error opening infile\n");
		p.outfile = open(av[argc -1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (p.outfile < 0)
			safe_exit("Error opening outfile\n");
	}
	prev_pipe = p.infile;
	p.i = -1;
	while (++p.i < cmd_count)
	{
		if (p.i < cmd_count - 1)
			if (pipe(p.pipe_fd) == -1)
				safe_exit("Pipe failed\n");
		child_pid = fork();
		if (child_pid == -1)
			safe_exit("Fork failed\n");
		if (child_pid == 0) // CHILD
		{
			if (p.i == cmd_count - 1)
				next_pipe = p.outfile;
			else
				next_pipe = p.pipe_fd[1];
			child_process(cmds[p.i], p.infile, p.outfile, prev_pipe, next_pipe);
		}
		else // PARENT
			prev_pipe = parent_process(p.pipe_fd, prev_pipe, child_pid);
	}
	close(prev_pipe);
	close(p.outfile);
	while (wait(NULL) > 0)
		;
}

void	child_process(t_cmd cmd, int infile_fd, int outfile_fd, int prev_pipe, int next_pipe)
{
	if (prev_pipe)
		dup2(prev_pipe, STDIN_FILENO);
	else
		dup2(infile_fd, STDIN_FILENO);
	if (next_pipe)
		dup2(next_pipe, STDOUT_FILENO);
	else
		dup2(outfile_fd, STDOUT_FILENO);
	if (prev_pipe)
		close(prev_pipe);
	if (next_pipe)
		close(next_pipe);
	close(infile_fd);
	close(outfile_fd);
	execve(cmd.path, cmd.args, NULL);
	perror("execve error");
	exit(127);
}

int	parent_process(int pipe_fd[2], int prev_pipe, pid_t child_pid)
{
	close(pipe_fd[1]);
	if (prev_pipe >= 0 && prev_pipe != STDIN_FILENO)
		close(prev_pipe);
	waitpid(child_pid, NULL, 0);
	return (pipe_fd[0]);
}
