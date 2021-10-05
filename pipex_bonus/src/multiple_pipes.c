/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:38:43 by julian            #+#    #+#             */
/*   Updated: 2021/10/04 15:11:02 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	multiple_pipes(int argc, char *argv[], char *envp[])
{
	t_mp	mp;
	int		*check_cmd;
	int		i;

	mp.f1 = open(argv[1], O_RDONLY);
	mp.f2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (mp.f1 < 0)
		return (pr_error(strerror(errno), argv[1]));
	if (mp.f2 < 0)
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
	mp.argc = argc;
	mp.argv = argv;
	mp.envp = envp;
	pipe_fork(&mp);
}
