/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 08:32:43 by julian            #+#    #+#             */
/*   Updated: 2021/08/19 15:54:35 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_pipex
{
	int		f1;
	int		f2;
	char	**paths;
	int		fd[2];
	pid_t	parent;
	pid_t	child1;
	pid_t	child2;	
	char	**cmd1;
	char	**cmd2;
}			t_pipex;

#endif