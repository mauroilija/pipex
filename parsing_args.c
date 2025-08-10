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

void    arg_parsing(int argc, char **argv, char ***envp)
{
    p_pipex p;
    char    **cmd_arr;

    p.i = 2;
    p.fd1= open("input.txt", O_RDONLY);
    if (p.fd1 < 0)
        safe_exit("Could not open/create file1\n");
    p.fd2 = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644); //0644 = user can read+write
    if (p.fd2 < 0)
        safe_exit("Could not open/create file2\n");
    while (p.i < argc - 2)
    {
        cmd_arr = ft_split(argv[p.i], ' ');
        if (!cmd_arr)
            return (free_split(cmd_arr));
        p.j = 0;
        while (cmd_arr[p.j])
        {
            get_path(cmd_arr[p.i], cmd_arr);
            p.j++;
        }
        p.i++;
    }
}

char    *get_path(const char  *cmd, char **envp)
{
    p_pipex p;
    char **path;
    char *cmd_path;
    char *full_path;

    if (cmd[p.i++] == '/')
    {
        if (access(cmd, F_OK | R_OK | X_OK) == 0)
            return (cmd);
    }
    if (!envp)
        return (NULL);
    p.i = 0;
    path = NULL;
    while (envp[p.i] != NULL)
    {
        if (strncmp(envp[p.i], "PATH=", 5) == 0)
        {
            path = envp[p.i + 5];
            if (!path)    
                free_split(path);
            break ;
            p.i++;
        }
    }
    cmd_path = ft_split(path, ':');
    if (!cmd_path)
        return (NULL);
    p.i = 0;
    while (cmd_path[p.i])
    {
       full_path = ft_strjoin(cmd_path, '/');
        if (access(cmd, F_OK | R_OK | X_OK) == 0)
        
    }
    return (NULL);
}

char *here_doc(char *str, char *limiter)
{
    p_pipex p;

    p.i = 0;
    while (p.i != limiter)
    {
        if (str[p.i] == "here_doc.txt")
        {
            
        }
        p.i++;
    }
    return;
}
