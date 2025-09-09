/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:52:50 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/09 09:11:24 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*normal_parsing(int argc, char **av, char **envp, int start)
{
	t_pipex	*p;
	t_cmd	c;

	p = malloc(sizeof(t_pipex));
	if (!p)
		return (NULL);
	p->cmd_count = argc - start - 1;
	p->cmds = ft_calloc((p->cmd_count + 1), sizeof(t_cmd));
	if (!p->cmds)
		return (free(p), NULL);
	p->i = start;
	p->index = 0;
	while (p->i < argc - 1)
	{
		c.args = ft_split(av[p->i], ' ');
		if (!c.args)
			return (free_pipex(p), NULL);
		if (!c.args[0])
			return (free_split(c.args), free_pipex(p), NULL);
		c.path = get_path(c.args[0], envp);
		if (!c.path)
			return (free_split(c.args), free_pipex(p), NULL);
		p->cmds[p->index].args = c.args;
		p->cmds[p->index].path = c.path;
		p->index++;
		p->i++;
	}
	p->cmds[p->index].args = NULL;
	p->cmds[p->index].path = NULL;
	return (p);
}

char	*get_path(char *cmd, char **envp)
{
	char	*path_line;
	char	**directories;
	char	*result;

	result = absolute_path(cmd);
	if (result)
		return (result);
	path_line = get_path_line(envp);
	if (!path_line)
		return (NULL);
	directories = ft_split(path_line, ':');
	if (!directories)
		return (free(path_line), NULL);
	result = fill_full_path(directories, cmd);
	if (!result)
		return (free_split(directories), NULL);
	free_split(directories);
	free(path_line);
	return (result);
}

char	*absolute_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	return (NULL);
}

char	*get_path_line(char **envp)
{
	t_pipex		p;
	char		*path_line;

	p.i = 0;
	while (envp[p.i])
	{
		if (ft_strncmp(envp[p.i], "PATH=", 5) == 0)
		{
			path_line = ft_strdup(envp[p.i] + 5);
			if (!path_line)
			{
				return (free(path_line), NULL);
			}
			return (path_line);
		}
		p.i++;
	}
	return (NULL);
}

char	*fill_full_path(char **directories, char *cmd)
{
	t_pipex		p;
	char		*result;

	p.i = -1;
	while (directories[++p.i])
	{
		p.bufsize = ft_strlen(directories[p.i]) + 1 + ft_strlen(cmd) + 1;
		p.full_path = malloc(p.bufsize);
		if (!p.full_path)
			return (free_split(directories), NULL);
		ft_strlcpy(p.full_path, directories[p.i], p.bufsize);
		ft_strlcat(p.full_path, "/", p.bufsize);
		ft_strlcat(p.full_path, cmd, p.bufsize);
		if (access(p.full_path, X_OK) == 0)
		{
			result = ft_strdup(p.full_path);
			if (!result)
				return (free(p.full_path), NULL);
			free(p.full_path);
			return (result);
		}
		free(p.full_path);
	}
	return (NULL);
}
