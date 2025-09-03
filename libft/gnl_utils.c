/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:04:27 by milija-h          #+#    #+#             */
/*   Updated: 2025/09/03 12:04:35 by milija-h         ###   ########.fr       */
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
