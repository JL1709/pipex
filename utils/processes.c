/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:03:52 by julian            #+#    #+#             */
/*   Updated: 2021/08/30 15:08:57 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/*
** "env" in terminal -> PATH=... (shows each possible path)
** dub2() - duplicate file descriptor
**	->	to use our files as stdin and stdout
** always close fd you don't use
** execve() - execute programm / file
** execve() transforms the calling process into a new process.
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
		if (execve(cmd, cmd1, envp) != -1)
			exit_success(path, cmd1, cmd);
		free(cmd);
	}
	exit_failure(path, cmd1);
}

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
		return(perror("PARENT_PROCESS: "));
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
		if (execve(cmd, cmd2, envp) != -1)
			exit_success(path, cmd2, cmd);
		free(cmd);
	}
	exit_failure(path, cmd2);
}
