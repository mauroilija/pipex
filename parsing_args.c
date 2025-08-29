/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:52:50 by milija-h          #+#    #+#             */
/*   Updated: 2025/08/29 07:59:35 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*this function builds a struct with al commands
    -we start off by opening the infile and creating the outfile
    -we dynamically allocate memory for the struct
    -and iterate from the first arg after infile to the arg before outfile, we
    split the args by space (by word), use our get path function to save the path
    of the the command in path and fill the struct up, so we can then return it
*/
t_pipex   normal_parsing(int argc, char **av, char **envp)
{
    t_pipex p;
    t_cmd   c;

    p.infile = open(av[1], O_RDONLY);
    p.outfile = open(av[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
    p.cmd_count = argc - 3;
    p.cmds = malloc((p.cmd_count) * sizeof(t_cmd));
    if (!p.cmds)
        safe_exit("Malloc error\n");
    p.i = 2;
    p.index = 0;
    while (p.i < argc - 1)
    {
        c.args = ft_split(av[p.i], ' '); //issue with **av instead of av?
        if (!c.args)
            safe_exit("Error splitting\n");
        c.path = get_path(c.args[0], envp);
        if (!c.path)
            safe_exit("Command not found\n");
        p.cmds[p.index].args = c.args;
        p.cmds[p.index].path = c.path;
        p.index++;
        p.i++;
    }
    return (p);
}

/*this function checks if the output command exists and is executable
    -first we check for the possibility of having absolute/relative paths, normally
separated by '/'
    -if the previous if is not met, we look for the full path in the envp:
    we find the PATH= and create a new array that holds everything after the '='
    we afterwards split it into ':' and store in a directories array, then we build our
    full path by dynamically allocating it and copying directorie into it and concatena-
    ting into it '/' + 'cmd', later we check with access if the command exist and is
    executable, if so, we return a duplicate of it and free the utilities
*/
char *get_path(char *cmd, char **envp)
{
    char    *path_line; // dup string of envp
    char    **directories;
    char    *result;

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
        return(free_split(directories), NULL);
    free_split(directories);
    return (result);
}

char    *absolute_path(char *cmd)
{
    if (ft_strchr(cmd, '/')) //checking for absolute and relative path
    {
        if (access(cmd, X_OK) == 0)
            return (ft_strdup(cmd));
        else
            return (NULL);
    }
    return (NULL);
}

char    *get_path_line(char **envp)
{
    t_pipex p;
    char    *path_line;;

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

char    *fill_full_path(char **directories, char *cmd)
{
    t_pipex p;
    char    *result;

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
