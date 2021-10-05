/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 08:40:19 by julian            #+#    #+#             */
/*   Updated: 2021/10/05 09:02:44 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
** O_TRUNC - truncated file to length 0 if file already exists
*/

int	main(int argc, char *argv[], char *envp[])
{
	if ((ft_strcmp(argv[1], "here_doc") == 0))
		here_doc(argv, envp);
	else
		multiple_pipes(argc, argv, envp);
	//system("leaks pipex");
	return (0);
}
