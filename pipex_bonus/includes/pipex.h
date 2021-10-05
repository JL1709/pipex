/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 08:32:43 by julian            #+#    #+#             */
/*   Updated: 2021/10/04 18:05:59 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

typedef struct s_mp
{
	int		argc;
	char	**argv;
	char	**envp;
	int		f1;
	int		f2;
}			t_mp;


void	exit_failure(char **path, char **cmd_n);
void	pipe_fork(t_mp *mp);
void	free_array(char **src);
char	**get_path(char *envp[]);
void	pr_error(char *s1, char *s2);
int		check_command(char *argv[], char *envp[], int position);
void	multiple_pipes(int argc, char *argv[], char *envp[]);
void	here_doc(char *argv[], char *envp[]);
void	child_process(t_mp *mp, int fd[][2], int i);

#endif
