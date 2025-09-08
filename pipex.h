/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 17:18:12 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/08 11:45:36 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define BUFFER_SIZE 100

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_cmd
{
	char	**args;
	char	*path;
	char	**envp;
	int		next_pipe;
}	t_cmd;

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		heredoc;
	int		status;
	int		cmd_count;
	int		pipe_fd[2];
	int		prev_pipe;
	char	*limiter;
	char	*full_path;
	pid_t	*child_pids;
	pid_t	exit_code;
	t_cmd	*cmds;
	char	**envp;
	size_t	j;
	int		i;
	size_t	index;
	size_t	bufsize;
}	t_pipex;

typedef struct s_vars
{
	char		*lines;
	char		*buffer;
	size_t		new_len;
	size_t		len;
}	t_vars;

//main
int			main(int argc, char **argv, char **envp);
//parsing
char		*absolute_path(char *cmd);
char		*get_path_line(char **envp);
char		*fill_full_path(char **directories, char *cmd);
t_pipex		*normal_parsing(int argc, char **av, char **envp, int start);
char		*get_path(char *cmd, char **envp);
char		*here_doc_reader(char *limiter);
//execution
int			execute(t_cmd *cmds, int argc, char **av, int cmd_count);
void		child_process(t_cmd cmd, int prev_pipe, t_pipex *p);
pid_t		execute(t_cmd *cmds, int argc, char **av, int cmd_count);
void		processes(t_cmd *cmds, t_pipex *p);
void		execute_here_doc(char **av, int argc, char **envp);
pid_t		exit_codee(pid_t *child_pids, int cmd_count);
//utils
void		safe_exit(char *str);
void		free_split(char **split);
void		free_pipex(t_pipex *p);

#endif
