/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:19:46 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/10 16:47:30 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_cmd cmd, int prev_pipe, t_pipex *p)
{
	if (p->infile != -1 && prev_pipe != -1)
		dup2(prev_pipe, STDIN_FILENO);
	else if (p->infile != STDIN_FILENO)
		dup2(p->infile, STDIN_FILENO);
	if (cmd.next_pipe != -1)
	{
		dup2(cmd.next_pipe, STDOUT_FILENO);
		close(cmd.next_pipe);
	}
	else if (p->outfile != STDOUT_FILENO)
		dup2(p->outfile, STDOUT_FILENO);
	if (access(cmd.path, F_OK) != 0)
	{
		ft_printf("%s: command not found\n", cmd.args[0]);
		exit(127);
	}
	if (access(cmd.path, X_OK) != 0)
	{
		ft_printf("%s: permission denied\n", cmd.args[0]);
		exit(126);
	}
	execve(cmd.path, cmd.args, cmd.envp);
	perror(cmd.args[0]);
	exit(126);
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
	{
		if (p->pipe_fd[0] != 0)
			close(p->pipe_fd[0]);
		p->prev_pipe = -1;
	}
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
			cmds[i].next_pipe = -1;
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

void	open_files(int argc, char **av, t_pipex *p)
{
	if (argc > 1 && !ft_strncmp(av[1], "here_doc", 8))
	{
		p->infile = open("temporary.txt", O_RDONLY);
		p_error_exit(av[1], p->infile);
		p->outfile = open(av[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0664);
		p_error_exit(av[argc -1], p->outfile);
	}
	else if (argc > 1 && access(av[1], F_OK) == 0)
	{
		p->infile = open(av[1], O_RDONLY);
		p_error_exit(av[1], p->infile);
		p->outfile = open(av[argc -1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
		p_error_exit(av[argc -1], p->outfile);
	}
	else
	{
		ft_printf("bash: ");
		perror(av[1]);
		exit(1);
	}
}

pid_t	execute(t_cmd *cmds, int argc, char **av, int cmd_count)
{
	t_pipex	p;

	p.cmd_count = cmd_count;
	open_files(argc, av, &p);
	p.prev_pipe = -1;
	p.child_pids = ft_calloc(cmd_count, sizeof(pid_t));
	if (!p.child_pids)
		exit(1);
	processes(cmds, &p);
	if (p.infile != STDIN_FILENO)
		close(p.infile);
	if (p.outfile != STDOUT_FILENO)
		close(p.outfile);
	p.exit_code = last_exit_code(p.child_pids, cmd_count);
	free(p.child_pids);
	return (p.exit_code);
}
