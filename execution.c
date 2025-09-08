/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:19:46 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/08 15:11:18 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// check for exit codes echo $?
//this functions execute all the necessary commands
void	child_process(t_cmd cmd, int prev_pipe, t_pipex *p) // good
{
	if (prev_pipe != -1)
		dup2(prev_pipe, STDIN_FILENO);
	else
		dup2(p->infile, STDIN_FILENO);
	if (cmd.next_pipe != -1)
		dup2(cmd.next_pipe, STDOUT_FILENO);
	else
		dup2(p->outfile, STDOUT_FILENO);
	if (prev_pipe != -1)
		close(prev_pipe);
	if (cmd.next_pipe != -1)
	{
		close(cmd.next_pipe);
	}
	execve(cmd.path, cmd.args, cmd.envp);
	perror("execve");
	exit(127);
}

void	parent_process(t_pipex *p, int i)
{
	if (p->prev_pipe != -1)
		close(p->prev_pipe);
	if (i < p->cmd_count - 1)
	{
		close(p->pipe_fd[1]);
		p->prev_pipe = p->pipe_fd[0];
	}
	else
		p->prev_pipe = -1;
}

void	processes(t_cmd *cmds, t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->cmd_count)
	{
		if (i < p->cmd_count - 1)
		{
			if (pipe(p->pipe_fd) == -1)
				exit(1);
			cmds[i].next_pipe = p->pipe_fd[1];
		}
		else
		{
			cmds[i].next_pipe = -1;
		}
		p->child_pids[i] = fork();
		if (p->child_pids[i] == -1)
			exit(1);
		if (p->child_pids[i] == 0)
			child_process(cmds[i], p->prev_pipe, p);
		else
			parent_process(p, i);
		i++;
	}
}

pid_t	execute(t_cmd *cmds, int argc, char **av, int cmd_count)
{
	t_pipex	p;

	p.cmd_count = cmd_count;
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
	p.prev_pipe = -1;
	p.child_pids = ft_calloc(cmd_count, sizeof(pid_t));
	if (!p.child_pids)
		exit(1);
	processes(cmds, &p);
	close(p.infile);
	close(p.outfile);
	p.exit_code = exit_codee(p.child_pids, cmd_count);
	free(p.child_pids);
	return (p.exit_code);
}
