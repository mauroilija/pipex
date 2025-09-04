/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:19:46 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/04 19:44:11 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// check for exit codes echo $?
//this functions execute all the necessary commands
int	execute(t_cmd *cmds, int argc, char **av, int cmd_count)
{
	t_pipex	p;
	int		prev_pipe;
	int		next_pipe;
	pid_t	*child_pids;
	pid_t	child_pid;
	pid_t	exit_code;

	if (argc > 1 && ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		p.infile = open("temp_file.txt", O_RDONLY);
		p.outfile = open(av[argc -1], O_CREAT | O_WRONLY | O_APPEND, 0664);
	}
	else
	{
		p.infile = open(av[1], O_RDONLY);
		p.outfile = open(av[argc -1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	}
	if (p.infile < 0 || p.outfile < 0)
		exit(74);
	prev_pipe = p.infile;
	child_pids = malloc(sizeof(pid_t));
	if (!child_pids)
		return (0);
	p.i = -1;
	child_pid = 0;
	while (++p.i < cmd_count)
	{
		if (p.i < cmd_count - 1)
			if (pipe(p.pipe_fd) == -1)
				exit (-1);
		child_pid = fork();
		if (child_pid == -1)
			exit (-1);
		if (child_pid == 0) // CHILD
		{
			if (p.i == cmd_count - 1)
				next_pipe = p.outfile;
			else
				next_pipe = p.pipe_fd[1];
			child_process(cmds[p.i], p.infile, p.outfile, prev_pipe, next_pipe);
		}
		else // PARENT
		{
			child_pids[p.i] = child_pid;
			if (p.i < cmd_count - 1)
				close(p.pipe_fd[1]);
			if (prev_pipe != p.infile)
				close (prev_pipe);
			if (p.i < cmd_count - 1)
				close(p.pipe_fd[0]);
		}
	}
	free(child_pids);
	close(prev_pipe);
	close(p.outfile);
	exit_code = 0;
	p.i = 0;
	while (p.i < cmd_count -1)
	{
		p.status = wait(&child_pid);
		if (WIFEXITED(p.status))
			exit_code = WEXITSTATUS(p.status);
		else if (WIFSIGNALED(p.status))
			exit_code = 128 + WTERMSIG(p.status);
		p.i++;
	}
	return (exit_code);
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

