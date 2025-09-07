/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:22:33 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/07 15:10:48 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	//pid_t	status;

	//status = 0;
	if (argc >= 4)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			execute_here_doc(argv, argc, envp);
		}
		else
		{
			p = normal_parsing(argc, argv, envp, 2);
			execute(p.cmds, argc, argv, p.cmd_count);
		}
	}
	//free(p.cmds);
	return (0);
}
