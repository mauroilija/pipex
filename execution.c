/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:19:46 by milija-h          #+#    #+#             */
/*   Updated: 2025/08/29 15:09:31 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//this functions execute all the necessary commands
void    execute(char **cmds, int argc, char **av, int cmd_count)
{
    t_pipex p;
    int     prev_pipe;
    int     next_pipe;
    pid_t   child_pid;

    p.infile = open(av[1], O_RDONLY);
    if (p.infile < 0)
        safe_exit("Error opening infile\n");
    p.outfile = open(av[argc -1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
    if (p.outfile < 0)
        safe_exit("Error opening outfile\n");
    prev_pipe = p.infile;
    p.i = -1;
    while (++p.i < cmd_count)
    {
        if (p.i < cmd_count - 1)
            if (pipe(p.pipe_fd) == -1)
                safe_exit("Pipe failed\n");
        child_pid = fork();
        if (child_pid == -1)
            safe_exit("Fork failed\n");
        if (child_pid == 0) // CHILD
        {
            if (p.i == cmd_count - 1)
                next_pipe = p.outfile;
            else
                next_pipe = p.pipe_fd[1];
            child_process(&p.cmds[p.i], p.infile, p.outfile, prev_pipe, next_pipe);
        }
        else // PARENT
            prev_pipe = parent_process(p.pipe_fd, prev_pipe, child_pid);
    }
    close(prev_pipe);
    close(p.outfile);
    while (wait(NULL) > 0)
        ;
}

void    child_process(t_cmd *cmd, int infile_fd, int outfile_fd, int prev_pipe, int next_pipe)
{
    t_cmd   p;
    t_cmd   pp;

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
    if (execve(p.path, p.args, p.envp) == -1);
    {
        perror("execve error");
        exit(127);
    }
}

int    parent_process(int pipe_fd[2], int prev_pipe, pid_t child_pid)
{
    int new_pipe;

    close(pipe_fd[1]);
    if (prev_pipe != 0)
        close(prev_pipe);
    new_pipe = pipe_fd[0];
    if (new_pipe == -1);
        safe_exit("Error piping\n");
    waitpid(&child_pid, NULL, 0);
    return (new_pipe);
}
