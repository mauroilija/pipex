/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:22:33 by milija-h          #+#    #+#             */
/*   Updated: 2025/08/06 17:22:34 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char ***envp)
{
	if (argc < 5)
		safe_exit("Not enough arguments to execute the program\n");
	else
		argv[1] = "input.txt";
		argv[argc - 1] = "output.txt"
}