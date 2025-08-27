/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:22:33 by milija-h          #+#    #+#             */
/*   Updated: 2025/08/27 13:14:55 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void debug_pipex(t_pipex p)
{
    int i = 0;
    size_t j;

    printf("infile fd: %d\n", p.infile);
    printf("outfile fd: %d\n", p.outfile);
    printf("cmd_count: %d\n", p.cmd_count);
    while (i < p.cmd_count)
    {
        if (!p.cmds[i].path)
            printf("cmd[%d].path = (null)\n", i);
        else
			printf("cmd[%d].path = %s\n", i, p.cmds[i].path);
        j = 0;
        if (p.cmds[i].args)
        {
            while (p.cmds[i].args[j])
            {
                printf("   arg[%zu] = %s\n", j, p.cmds[i].args[j]);
                j++;
            }
        }
        else
        {
            printf("   args = (null)\n");
        }
        i++;
    }
}

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 4)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			here_doc_reader(LIMITER);
		}
		else
		{
			//normal_parsing(argc, argv, envp);
			t_pipex p = normal_parsing(argc, argv, envp);
            debug_pipex(p);
		}
	}
	return (0);
}

/*int main(int argc, char **argv, char **envp)
{
    if (argc > 1)
    {
        if (ft_strncmp(argv[1], "here_doc\0", 9) == 0)
        {
            char *result = here_doc_reader(argv[2]); // pass limiter
            if (result)
            {
                printf("Captured heredoc content:\n%s", result);
                free(result);
            }
            else
                printf("here_doc_reader returned NULL\n");
        }
        else
        {
            t_pipex p = normal_parsing(argc, argv, envp);
            debug_pipex(p);
            // TODO: free cmds, args, path when you’re done
        }
    }
    return (0);
}*/