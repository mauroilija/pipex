/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:52:33 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/10 17:04:01 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	safe_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	free_split(char **split)
{
	size_t	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	last_exit_code(pid_t *child_pids, int cmd_count)
{
	int		i;
	int		status;
	int		exit_code;
	pid_t	pid;

	exit_code = 0;
	i = 0;
	while (i < cmd_count)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			continue ;
		if (pid == child_pids[cmd_count - 1])
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
			else
				exit_code = 1;
		}
		i++;
	}
	return (exit_code);
}

void	free_pipex(t_pipex *p)
{
	int	i;

	if (!p || !p->cmds)
		return ;
	i = 0;
	while (i < p->cmd_count)
	{
		free_split(p->cmds[i].args);
		free(p->cmds[i].path);
		i++;
	}
	free (p->cmds);
	free(p);
}

void	p_error_exit(char *str, int fd)
{
	if (fd < 0)
	{
		perror(str);
		exit (1);
	}
}
