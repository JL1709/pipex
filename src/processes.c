/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:03:52 by julian            #+#    #+#             */
/*   Updated: 2021/10/02 16:01:25 by jludt            ###   ########.fr       */
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

void	child_process(int f1, int f2, int fd[][2], char *argv[], char *envp[], int j, int max_it)
{
	int		i;
	char	*cmd;
	char	**path;
	char	**cmd1;

	fprintf(stderr, "j = %d\n", j);
	if (j == 0)
	{
		fprintf(stderr, "j == 0\n");
		if (dup2(f1, STDIN_FILENO) < 0 || dup2(fd[0][1], STDOUT_FILENO) < 0)
			return (perror("CHILD_PROCESS: "));
		close(f1);
		close(fd[0][0]);
	}
	else if (j == max_it)
	{
		fprintf(stderr, "j == max_it\n");
		if (dup2(fd[1][0], STDIN_FILENO) < 0 || dup2(f2, STDOUT_FILENO) < 0)
			return (perror("CHILD_PROCESS: "));
		close(fd[1][1]);
		close(fd[0][1]);
		close(fd[0][0]);
		close(f2);
	}
	else
	{
		fprintf(stderr, "j == in between\n");
		if (dup2(fd[j - 1][0], STDIN_FILENO) < 0 || dup2(fd[j][1], STDOUT_FILENO) < 0)
		//if (dup2(fd[0][0], STDIN_FILENO) < 0)
			return (perror("CHILD_PROCESS: "));
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[1][1]);
	}
	path = get_path(envp);
	cmd1 = ft_split(argv[j + 2], ' ');
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
