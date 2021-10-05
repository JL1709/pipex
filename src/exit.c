/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:03:21 by julian            #+#    #+#             */
/*   Updated: 2021/09/12 13:34:23 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_array(char **src)
{
	int	i;

	i = 0;
	while (src[i] != NULL)
		free(src[i++]);
	free(src);
	i = 0;
}

void	exit_failure(char **path, char **cmd_n)
{
	free_array(path);
	free_array(cmd_n);
	exit(EXIT_FAILURE);
}
