/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:19:46 by milija-h          #+#    #+#             */
/*   Updated: 2025/08/28 17:03:27 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "pipex.h"


    this functions execute all the necessary commands


void    execute(int argc, char **av, int cmd_count)
{
    t_pipex p;
    int fd[2];
    pid_t   pid;

    p.infile = open(av[1], O_RDONLY);
    p.outfile = open(av[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
    p.i = 0;
    while (p.i < cmd_count)
    {
        if (p.i != cmd_count)
        {
            pipe(fd);
            if (fd == -1)
                safe_exit("Error piping\n");
            break ;
        }
        else
        {
            pid = fork();
            if (pid == -1)
                safe_exit("Error piping\n");
            if (pid == 0) // if child
            {
                if (cmd_count == 1)
                {
                    dup2(p.infile, STDIN_FILENO);
                    dup2(p.outfile, STDOUT_FILENO);
                }
            }
            else
            {    
                close(fd[2]);
                waitpid(pid, NULL, 0);
            }
        }
    }
}
void    child_processes(char *av, char **envp)
{
    
}*/