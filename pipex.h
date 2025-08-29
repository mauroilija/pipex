/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:18:12 by milija-h          #+#    #+#             */
/*   Updated: 2025/08/29 15:26:40 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define LIMITER "EOF"
# define BUFFER_SIZE 100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/libft.h"

typedef struct s_cmd
{
    char **args;
    char *path;
    char **envp
}   t_cmd;

typedef struct s_pipex
{
    int     infile;
    int     outfile;
    int     heredoc;
    int     i;
    int     cmd_count;
    int     pipe_fd[2];
    char    *limiter;
    char    *lines;
    char    *full_path;
    t_cmd   *cmds;
    size_t  j;
    size_t  index;
    size_t  bufsize;
}   t_pipex;

//main
int         main(int argc, char **argv, char **envp);
//parsing
char        *absolute_path(char *cmd);
char        *get_path_line(char **envp);
char        *fill_full_path(char **directories, char *cmd);
t_pipex     normal_parsing(int argc, char **av, char **envp);
char        *get_path(char *cmd, char **envp);
char        *here_doc_reader(char *limiter);
//execution
void    execute(char **cmds, int argc, char **av, int cmd_count);
void    child_process(t_cmd *cmd, int infile_fd, int outfile_fd, int prev_pipe, int next_pipe);
int    parent_process(int pipe_fd[2], int prev_pipe, pid_t child_pid);
//utils
void        safe_exit(char *str);
void        free_split(char **split);

#endif
