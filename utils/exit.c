/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:03:21 by julian            #+#    #+#             */
/*   Updated: 2021/08/30 17:20:17 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_array(char **src)
{
	int	i;
	
	i = 0;
	while (src[i] != NULL)
		free(src[i++]);
	free(src);
	i = 0;
}

void	exit_success(char **path, char **cmd_n, char *cmd)
{
	free_array(path);
	free_array(cmd_n);
	free(cmd);
	exit(EXIT_SUCCESS);
}

void	exit_failure(char **path, char **cmd_n)
{
	free_array(path);
	free_array(cmd_n);
	exit(EXIT_FAILURE);
}
