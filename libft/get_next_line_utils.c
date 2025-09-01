/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:18:20 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/01 17:19:40 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_stash_if_line_null(char *stash, char *line)
{
	if (!line)
	{
		free(stash);
		stash = NULL;
	}
	return (stash);
}
