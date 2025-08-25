/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:52:50 by milija-h          #+#    #+#             */
/*   Updated: 2025/08/06 17:52:52 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    arg_parsing(int argc, char **av, char ***envp)
{
    t_pipex p;
    t_cmd   c;

    p.infile = open("input_file.txt", O_CREAT | O_WRONLY | O_TRUNC , 0664);
    p.outfile = open("output_file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0664);
    p.i = 2;
    while (p.i < argc - 2)
    {
        c.args = ft_split(av[p.i], ' '); //issue with **av instead of av?
        if (!c.args)
            safe_exit("Error splitting\n");
        c.path = get_path(c.args[0], envp);
        p.i++;
    }
}

/*this function checks if the output command exists and is executable
    -first we check for the possibility of having absolute/relative paths, normally
separated by '/'
    -if the previous if is not met, we look for the full path in the envp:
    we find the PATH= and create a new array that holds everything after the '='
    we afterwards split it into ':' and use access to check if the command found exists
    and is executable, if so, we return that value and free the previous array
*/
char *get_path(char *cmd, char **envp)
{
    t_pipex p;
    char    **cmd_args;
    char    **path_line;
    char    **full_path;

    if (ft_strchr(cmd, '/')) //checking for absolute/relative path
    {
        if (access(cmd_args[p.j], X_OK) == 0)
            return (ft_strdup(cmd));
        else
            return (NULL);
    }
    else //get path enviroment
    {
        p.i = 0;
        while (envp[p.i])
        {
            if (ft_strncmp(envp[p.i], "PATH=", 5) == 0)
            {
                path_line = ft_strdup(envp[p.i] + 5);
                if (!path_line)
                    return (free(path_line), NULL);
            }
            p.i++;
        }
        p.i = 0;
        while (path_line[p.i]) //potentially need to create a char* to return it?
        {
            full_path = ft_split(path_line, ':');
            if (!full_path)
                return (free_split(full_path), NULL);
            if (access(full_path, X_OK) == 0)
                return (free_split(path_line), full_path);
            free(full_path);
            p.i++;
        }
    }
    free_split(full_path);
    return (NULL);
}
