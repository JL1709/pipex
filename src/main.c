/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 08:40:19 by julian            #+#    #+#             */
/*   Updated: 2021/10/02 12:26:47 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
** O_TRUNC - truncated file to length 0 if file already exists
*/

int	main(int argc, char *argv[], char *envp[])
{
	int	f1;
	int	f2;
	int	i;
	int	*check_cmd;

	// if (argc != 5)
	// 	return (pr_error(0, "Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile"));
	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (f1 < 0)
		return (pr_error(strerror(errno), argv[1]));
	if (f2 < 0)
		return (pr_error(strerror(errno), argv[argc - 1]));
	check_cmd = (int *)malloc(sizeof(int) * (argc - 3));
	i = -1;
	while (++i < (argc - 3))
		check_cmd[i] = check_command(argv, envp, (i + 2));
	i = -1;
	while (++i < (argc - 3))
		if (check_cmd[i] == 0)
			exit(EXIT_FAILURE);
	free(check_cmd);
	pipe_fork(f1, f2, argv, envp, argc);
	return (0);
}
