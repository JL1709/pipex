/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 08:40:19 by julian            #+#    #+#             */
/*   Updated: 2021/09/09 13:10:12 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** pipe() - create pipe
**	->	send output of first execve() as input to second execve()
** fork() - create a child process
** 	->	run two processe (i. e. commands) in one single programm
*/

static void	pipex(int f1, int f2, char *argv[], char *envp[])
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

/*
** using 0644 will create a file that is Read/Write for owner, 
** and Read Only for everyone else
*/

int	main(int argc, char *argv[], char *envp[])
{
	int	f1;
	int	f2;
	int	check_cmd1;
	int	check_cmd2;

	if (argc != 5)
		return (pr_error(0, "Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile"));
	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0)
		return (pr_error(strerror(errno), argv[1]));
	if (f2 < 0)
		return (pr_error(strerror(errno), argv[4]));
	check_cmd1 = check_command(argv, envp, 2);
	check_cmd2 = check_command(argv, envp, 3);
	if (check_cmd1 == 0 || check_cmd2 == 0)
		exit(EXIT_FAILURE);
	pipex(f1, f2, argv, envp);
	return (0);
}
