/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 08:32:43 by julian            #+#    #+#             */
/*   Updated: 2021/10/02 14:50:26 by jludt            ###   ########.fr       */
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

void	exit_failure(char **path, char **cmd_n);
void	pipe_fork(int f1, int f2, char *argv[], char *envp[], int argc);
void	free_array(char **src);
char	**get_path(char *envp[]);
int		pr_error(char *s1, char *s2);
int		check_command(char *argv[], char *envp[], int position);
void	child1_process(int f1, int *fd, char *argv[], char *envp[], int i);
void	child2_process(int f2, int *fd, char *argv[], char *envp[], int i, int max_it);
void	child_process(int f1, int f2, int fd[][2], char *argv[], char *envp[], int j, int max_it);

#endif
