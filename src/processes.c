/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:03:52 by julian            #+#    #+#             */
/*   Updated: 2021/09/12 13:34:42 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
** env - set environment and execute command, or print environmenqt
** "env" in terminal -> PATH=... (shows each possible path)
** dub2("fd to copy", "(value of) new fd") - duplicate file descriptor
**	->	to use our files as stdin and stdout
** always close fd you don't use
** execve() - execute programm / file
** execve() overlays the current process image  with a new process image
** -> the successful call has no process to return to
*/

void	child_process(int f1, int *fd, char *argv[], char *envp[])
{
	int		i;
	char	*cmd;
	char	**path;
	char	**cmd1;

	if (dup2(f1, STDIN_FILENO) < 0 || dup2(fd[1], STDOUT_FILENO) < 0)
		return (perror("CHILD_PROCESS: "));
	close(fd[0]);
	close(f1);
	path = get_path(envp);
	cmd1 = ft_split(argv[2], ' ');
	i = -1;
	while (path[++i] != NULL)
	{
		cmd = ft_strjoin(path[i], cmd1[0]);
		if (cmd == NULL)
			return ;
		execve(cmd, cmd1, envp);
		free(cmd);
	}
	exit_failure(path, cmd1);
}

/*
** waitpid(-1, &status, 0) == wait(&status)
** The waitpid() system call suspends execution of the calling process 
** until a child specified by pid argument has changed state.
** -1 --> meaning wait for any child process
*/

void	parent_process(int f2, int *fd, char *argv[], char *envp[])
{
	int		status;
	int		i;
	char	*cmd;
	char	**path;
	char	**cmd2;

	status = 0;
	waitpid(-1, &status, 0);
	if (dup2(f2, STDOUT_FILENO) < 0 || dup2(fd[0], STDIN_FILENO) < 0)
		return (perror("PARENT_PROCESS: "));
	close(fd[1]);
	close(f2);
	path = get_path(envp);
	cmd2 = ft_split(argv[3], ' ');
	i = -1;
	while (path[++i] != NULL)
	{
		cmd = ft_strjoin(path[i], cmd2[0]);
		if (cmd == NULL)
			return ;
		execve(cmd, cmd2, envp);
		free(cmd);
	}
	exit_failure(path, cmd2);
}
