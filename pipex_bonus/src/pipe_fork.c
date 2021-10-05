/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:43:56 by julian            #+#    #+#             */
/*   Updated: 2021/10/04 15:34:55 by julian           ###   ########.fr       */
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

void	pipe_fork(t_mp *mp)
{
	int		fd[mp->argc - 4][2];
	pid_t	pid;
	int		i;

	i = -1;
	while (++i < (mp->argc - 4))
		pipe(fd[i]);
	i = -1;
	while (++i < (mp->argc - 3))
	{
		pid = fork();
		if (pid < 0)
			return (perror("FORK: "));
		if (pid == 0)
			child_process(mp, fd, i);
	}
	i = -1;
	while (++i < (mp->argc - 4))
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	i = -1;
	while (++i < (mp->argc - 3))
		wait(NULL);
}
