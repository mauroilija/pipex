/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milija-h <milija-h@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:28:03 by milija-h          #+#    #+#             */
/*   Updated: 2025/08/05 17:28:05 by milija-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*int main()
{
    int fd;

    fd = open("test.txt",   O_WRONLY | O_CREAT, 0644);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    printf("this is printed in example.txt!\n");
    return 0;
}

int main()
{
    if (access("test.txt", R_OK) != -1)
        printf("I have permission\n");
    else
        printf("No permission\n");
    return 0;
}

int main()
{
    char *args[3];

    args[0] = "ls";
    args[1] = "-l";
    args[2] = NULL;
    execve("/bin/ls", args, NULL);
    printf("This line wont be executed\n");
    return 0;
}

int main()
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
        printf("Hello from child: pid = %d\n", getpid());
    else
        printf("Hello from parent: pid = %d\n", getpid());
    return 0;
}
int main()
{
    int fd[2];
    pid_t pid;
    char buffer[13];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        close(fd[0]);
        write(fd[1], "Hello from parent!", 13);
        close(fd[1]);
        exit(EXIT_FAILURE);
    }
    else
    {
        close(fd[1]);
        read(fd[0], buffer, 13);
        close(fd[0]);
        printf("Message from child: '%s'\n", buffer);
        exit(EXIT_SUCCESS);
    }
}

int main()
{
    if (unlink("test.txt") == 0)
        printf("file deleted sucessfully\n");
    else
        printf("Error deleting the file\n");
    return 0;
}*/