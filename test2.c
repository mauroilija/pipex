/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:03:31 by milija-h          #+#    #+#             */
/*   Updated: 2025/08/07 20:03:32 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char *env_variable = getenv("PATH");
    printf("The value of our environment variable is: %s\n\n", env_variable);
    return 0;
}