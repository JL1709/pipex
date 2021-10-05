/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 08:40:19 by julian            #+#    #+#             */
/*   Updated: 2021/09/12 13:50:31 by julian           ###   ########.fr       */
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
	int	check_cmd1;
	int	check_cmd2;

	if (argc != 5)
		return (pr_error(0, "Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile"));
	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (f1 < 0)
		return (pr_error(strerror(errno), argv[1]));
	if (f2 < 0)
		return (pr_error(strerror(errno), argv[4]));
	check_cmd1 = check_command(argv, envp, 2);
	check_cmd2 = check_command(argv, envp, 3);
	if (check_cmd1 == 0 || check_cmd2 == 0)
		exit(EXIT_FAILURE);
	pipe_fork(f1, f2, argv, envp);
	return (0);
}
