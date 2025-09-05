/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:52:33 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/05 14:33:09 by milija-h         ###   ########.fr       */
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
	t_pipex	p;

	p.i = 0;
	while (split[p.i])
	{
		free(split[p.i++]);
	}
	free(split);
}

pid_t	exit_codee(pid_t *child_pids, int cmd_count)
{
	pid_t	exit_code;
	int		status;
	int		i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(child_pids[i], &status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (exit_code);
}
