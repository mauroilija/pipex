/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:18:12 by milija-h          #+#    #+#             */
/*   Updated: 2025/08/27 12:54:46 by milija-h         ###   ########.fr       */
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
    t_cmd   *cmds;
    size_t  j;
    size_t  index;
}   t_pipex;


int         main(int argc, char **argv, char **envp);
t_pipex     normal_parsing(int argc, char **av, char **envp);
void        safe_exit(char *str);
void        free_split(char **split);
char        *get_path(char *cmd, char **envp);
char        *here_doc_reader(char *limiter);

#endif
