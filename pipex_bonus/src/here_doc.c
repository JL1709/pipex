/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:10:12 by julian            #+#    #+#             */
/*   Updated: 2021/10/05 10:51:09 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	heredoc_prepare(int *fd_heredoc, char *argv[])
{
	char	*line;

	if (pipe(fd_heredoc) == -1)
	{
		perror("PIPE");
		exit(EXIT_FAILURE);
	}
	write(1, "pipe heredoc> ", 14);
	line = get_next_line(0);
	while (line)
	{
		line = ft_strtrim(line, "\n");
		if (ft_strcmp(line, argv[2]) == 0)
		{
			free(line);
			break ;
		}
		write(1, "pipe heredoc> ", 14);
		write(fd_heredoc[1], line, ft_strlen(line));
		write(fd_heredoc[1], "\n", 1);
		free(line);
		line = get_next_line(0);
	}
}

void	heredoc_child(char *argv[], char *envp[], int *fd)
{
	int		fd_heredoc[2];
	char	*cmd;
	char	**path;
	char	**cmd1;
	int		i;

	heredoc_prepare(fd_heredoc, argv);
	if ((dup2(fd_heredoc[0], STDIN_FILENO) < 0) || (dup2(fd[1], STDOUT_FILENO) < 0))
		return (perror("CHILD_PROCESS"));
	close(fd_heredoc[0]);
	close(fd_heredoc[1]);
	close(fd[0]);
	path = get_path(envp);
	cmd1 = ft_split(argv[3], ' ');
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

void	heredoc_parent(char *argv[], char *envp[], int *fd)
{
	char	*cmd;
	char	**path;
	char	**cmd1;
	int		i;
	int		f_out;

	wait(NULL);
	f_out = open(argv[5], O_CREAT | O_RDWR | O_APPEND, 0777);
	if (f_out < 0)
		return (pr_error(strerror(errno), argv[5]));
	close(fd[1]);
	if ((dup2(fd[0], STDIN_FILENO) < 0) || (dup2(f_out, STDOUT_FILENO) < 0))
		return (perror("PARENT_PROCESS"));
	close(fd[0]);
	path = get_path(envp);
	cmd1 = ft_split(argv[4], ' ');
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

void	here_doc(char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	pid;
	
	if (pipe(fd) == -1)
		return (perror("PIPE"));
	pid = fork();
	if (pid < 0)
		return (perror("FORK"));
	if (pid == 0)
		heredoc_child(argv, envp, fd);
	else
		heredoc_parent(argv, envp, fd);
}
