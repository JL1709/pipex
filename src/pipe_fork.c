/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:43:56 by julian            #+#    #+#             */
/*   Updated: 2021/10/02 16:09:36 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
** pipe() - create pipe -> send something from one process to another one
** -> get two file desciptors
** -> send output of first execve() as input to second execve()
** fd[0] - read
** fd[1] - write
** fork() - create a child process
** 	->	run two processe (i. e. commands) in one single programm
** waitpid(-1, &status, 0) == wait(&status)
** The waitpid() system call suspends execution of the calling process 
** until a child specified by pid argument has changed state.
** -1 --> meaning wait for any child process
*/

void	pipe_fork(int f1, int f2, char *argv[], char *envp[], int argc)
{
	int		fd[2][2];
	// int		status;
	pid_t	pid;
	int		i;

	// i = -1;
	// while (++i < (argc - 4))
	// 	pipe(fd[i]);
	pipe(fd[0]);
	pipe(fd[1]);
	i = 0;
	while (i < (argc - 3))
	{
		pid = fork();
		if (pid < 0)
			return (perror("FORK: "));
		if (pid == 0)
			child_process(f1, f2, fd, argv, envp, i, argc - 4);
			// vielleicht besser nur die fd's übergeben, die auch wirklich gebraucht werden und nicht fd[][]
		i++;
	}
	i = -1;
	while (++i < (argc - 4))
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	// status = 0;
	// i = -1;
	// while(++i < (argc - 4))
	// 	wait(&status);
	// while ((pid = waitpid(-1, &status, 0)) != -1);
		//fprintf(stderr, "Process %d terminated\n", pid);
}
