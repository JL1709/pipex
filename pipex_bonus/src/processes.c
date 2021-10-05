/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:03:52 by julian            #+#    #+#             */
/*   Updated: 2021/10/04 15:48:32 by julian           ###   ########.fr       */
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

static void	close_fds(t_mp *mp, int fd[][2])
{
	int i;

	i = -1;
	while (++i < mp->argc - 4)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	close(mp->f1);
	close(mp->f2);
}

static void	execute_cmd(t_mp *mp, int i)
{
	char	*cmd;
	char	**path;
	char	**cmd1;

	path = get_path(mp->envp);
	cmd1 = ft_split(mp->argv[i + 2], ' ');
	i = -1;
	while (path[++i] != NULL)
	{
		cmd = ft_strjoin(path[i], cmd1[0]);
		if (cmd == NULL)
			return ;
		execve(cmd, cmd1, mp->envp);
		free(cmd);
	}
	exit_failure(path, cmd1);
}

void	child_process(t_mp *mp, int fd[][2], int i)
{
	if (i == 0)
	{
		if (dup2(mp->f1, STDIN_FILENO) < 0 || dup2(fd[i][1], STDOUT_FILENO) < 0)
			return (perror("CHILD_PROCESS: "));
	}
	else if (i == mp->argc - 4)
	{
		if (dup2(fd[i - 1][0], STDIN_FILENO) < 0 || dup2(mp->f2, STDOUT_FILENO) < 0)
			return (perror("CHILD_PROCESS: "));
	}
	else
	{
		if (dup2(fd[i - 1][0], STDIN_FILENO) < 0 || dup2(fd[i][1], STDOUT_FILENO) < 0)
			return (perror("CHILD_PROCESS: "));
	}
	close_fds(mp, fd);
	execute_cmd(mp, i);
}
