/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:22:33 by milija-h          #+#    #+#             */
/*   Updated: 2025/08/26 17:23:17 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 4)
	{
		if (argv[1] == "here_doc")
		{
			here_doc_reader(LIMITER);
		}
		else
			normal_parsing(argc, argv, envp);
	}

	return (0);
}