/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 08:32:43 by julian            #+#    #+#             */
/*   Updated: 2021/09/06 13:56:35 by jludt            ###   ########.fr       */
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
# include <string.h>
# include <errno.h>

// typedef struct s_pipex
// {
// 	int		f1;
// 	int		f2;
// 	char	**paths;
// 	int		fd[2];
// 	pid_t	parent;
// 	pid_t	child1;
// 	pid_t	child2;	
// 	char	**cmd1;
// 	char	**cmd2;
// }			t_pipex;

void	exit_failure(char **path, char **cmd_n);
void	exit_success(char **path, char **cmd_n, char *cmd);
void	free_array(char **src);
char	**get_path(char *envp[]);
int		pr_error(char *s1, char *s2);
int		check_command(char *argv[], char *envp[], int position);
void	child_process(int f1, int *fd, char *argv[], char *envp[]);
void	parent_process(int f2, int *fd, char *argv[], char *envp[]);

#endif
