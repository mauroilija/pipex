/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:18:12 by milija-h          #+#    #+#             */
/*   Updated: 2025/08/26 17:22:14 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define LIMITER "EOF"
# define BUFFER_SIZE 42

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
    char    *limiter;
    t_cmd   *cmds;
    int     cmd_count;
    size_t  i;
    size_t  j;
    size_t  z;
    char    *lines;
}   t_pipex;


int         main(int argc, char **argv, char **envp);
t_pipex     normal_parsing(int argc, char **av, char **envp);
void        safe_exit(char *str);
void        free_split(char **split);
char        *get_path(char *cmd, char **envp);
char        *here_doc_reader(char *limiter);

#endif
