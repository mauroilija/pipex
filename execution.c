/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:19:46 by milija-h          #+#    #+#             */
/*   Updated: 2025/08/27 15:56:48 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
    this functions execute all the necessary commands

*/
void    execute(int argc, char **av, t_cmd cmd_count)
{
    t_pipex p;
    int pi[argc - 1];


    p.infile = open(av[1], O_RDONLY);
    p.outfile = open(av[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
    dup2(p.infile, STDIN_FILENO);
    dup2(p.outfile, STDOUT_FILENO);
    pipe(pi);
    p.i = 0;
    while (i < cmd_count)
    {
        
    }
    
    

}
