/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:52:33 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/03 13:05:07 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	safe_exit(char *str)
{
	perror(str),
	exit(EXIT_FAILURE);
}

void	free_split(char **split)
{
	t_pipex	p;

	p.i = 0;
	while (split[p.i])
	{
		free(split[p.i++]);
	}
	free(split);
}
