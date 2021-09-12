/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:43:56 by julian            #+#    #+#             */
/*   Updated: 2021/09/12 13:45:58 by julian           ###   ########.fr       */
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
*/

void	pipe_fork(int f1, int f2, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	id;

	pipe(fd);
	id = fork();
	if (id < 0)
		return (perror("FORK: "));
	if (id == 0)
		child_process(f1, fd, argv, envp);
	else
		parent_process(f2, fd, argv, envp);
}
