/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 15:48:28 by julian            #+#    #+#             */
/*   Updated: 2021/08/30 18:48:21 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/*
** access, faccessat -- check accessibility of a file
** The access() system call checks the accessibility of the file named by the
** path argument for the access permissions indicated by the mode argument.
** The value of mode is either the bitwise-inclusive OR of the access 
** permissions to be checked (R_OK for read permission, W_OK for 
** write permission, and X_OK for execute/search permission), 
** or the existence test (F_OK).
*/

int	pr_error(char *s1, char *s2)
{
	if (s1)
	{
		ft_putstr_fd("zsh: ", 2);
		ft_putstr_fd(s1, 2);
		ft_putstr_fd(": ", 2);
	}
	if (s2)
		ft_putstr_fd(s2, 2);
	write(2, "\n", 1);
	return(0);
}

static int	print_error_cmd(char *src)
{
	ft_putstr_fd("zsh: command not found: ", 2);
	ft_putstr_fd(src, 2);
	write(2, "\n", 1);
	return (0);
}

int	check_command (char *argv[], char *envp[], int position)
{
	int		i;
	char	*cmd;
	char	**path;
	char	**command;

	path = get_path(envp);
	command = ft_split(argv[position], ' ');
	i = -1;
	while (path[++i] != NULL)
	{
		cmd = ft_strjoin(path[i], command[0]);
		if (cmd == NULL)
			break;
		if (access(cmd, X_OK) != -1)
		{
			free(cmd);
			return(1);
		}
		free(cmd);
	}
	free_array(path);
	free_array(command);
	return (print_error_cmd(argv[position]));
}
