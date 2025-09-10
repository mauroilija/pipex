/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:22:33 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/10 17:03:20 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
	-leaking when command does not exits
	-exit status whe no infile

		-exit status double check
*/
int	main(int argc, char **argv, char **envp)
{
	t_pipex	*p;
	int		exit_code;

	exit_code = 0;
	if (argc < 5)
		ft_printf("Error: usage expects atleast 5 commands");
	else
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			execute_here_doc(argv, argc, envp);
		}
		else
		{
			p = normal_parsing(argc, argv, envp, 2);
			if (!p)
				safe_exit("Error\n");
			exit_code = execute(p->cmds, argc, argv, p->cmd_count);
			free_pipex(p);
		}
	}
	exit(exit_code);
}
