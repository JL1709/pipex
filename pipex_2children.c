/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_2children.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 08:40:19 by julian            #+#    #+#             */
/*   Updated: 2021/09/06 14:03:35 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_data(t_pipex *data, char *argv[], char *envp[])
{
	int	i;

	data->paths = ft_split(envp[4], ':');
	data->paths[0] = ft_strtrim(data->paths[0], "PATH=");
	i = -1;
	while (data->paths[++i] != NULL)
		data->paths[i] = ft_strjoin(data->paths[i], "/");
	data->cmd1 = ft_split(argv[2], ' ');
	data->cmd2 = ft_split(argv[3], ' ');
}

/*
** "env" in terminal -> PATH=... (shows each possible path)
** dub2() - duplicate file descriptor
**	->	to use our files as stdin and stdout
** always close fd you don't use
** execve() - execute programm
*/

static void	child1(t_pipex *data, char *envp[])
{
	int		i;
	char	*cmd;

	dup2(data->f1, STDIN_FILENO);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[0]);
	close(data->f1);
	i = -1;
	while (data->paths[++i] != NULL)
	{
		cmd = ft_strjoin(data->paths[i], data->cmd1[0]);
		execve(cmd, data->cmd1, envp);
		free(cmd);
	}
	exit(EXIT_FAILURE);
}

static void	child2(t_pipex *data, char *envp[])
{
	int		i;
	char	*cmd;

	dup2(data->f2, STDOUT_FILENO);
	dup2(data->fd[0], STDIN_FILENO);
	close(data->fd[1]);
	close(data->f2);
	i = -1;
	while (data->paths[++i] != NULL)
	{
		cmd = ft_strjoin(data->paths[i], data->cmd2[0]);
		execve(cmd, data->cmd2, envp);
		free(cmd);
	}
	exit(EXIT_FAILURE);
}

/*
** pipe() - create pipe
**	->	send output of first execve() as input to second execve()
** fork() - create a child process
** 	->	run two processe (i. e. commands) in one single programm
*/

static void	pipex(t_pipex *data, char *envp[])
{
	int	status;

	status = 0;
	pipe(data->fd);
	data->child1 = fork();
	if (data->child1 < 0)
		return (perror("FORK_CHILD1: "));
	if (data->child1 == 0)
		child1(data, envp);
	data->child2 = fork();
	if (data->child2 < 0)
		return (perror("FORK_CHILD2: "));
	if (data->child2 == 0)
		child2(data, envp);
	close(data->fd[0]);
	close(data->fd[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
}

/*
** Using 0644 will create a file that is Read/Write for owner, 
** and Read Only for everyone else
*/

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*data;

	data = (t_pipex *)malloc(sizeof(t_pipex));
	if (data == NULL)
		return (0);
	if (argc != 5)
		return (0);
	data->f1 = open(argv[1], O_RDONLY);
	data->f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->f1 < 0 || data->f2 < 0)
		return (-1);
	get_data(data, argv, envp);
	pipex(data, envp);
	free(data);
	return (0);
}
