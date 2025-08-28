/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:18:12 by milija-h          #+#    #+#             */
/*   Updated: 2025/08/28 17:02:13 by milija-h         ###   ########.fr       */
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
}   t_cmd;

typedef struct s_pipex
{
    int     infile;
    int     outfile;
    int     heredoc;
    int     i;
    int     cmd_count;
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
//utils
void        safe_exit(char *str);
void        free_split(char **split);


#endif
