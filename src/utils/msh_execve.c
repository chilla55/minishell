/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 09:17:00 by skorte            #+#    #+#             */
/*   Updated: 2022/05/05 16:35:05 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** searches the given command in current path and PATH
** and executes it in a child process.
**
*/

static void	mini_execve_free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static void	mini_execve_child(char *command, char **argv, char **envp)
{
	int		i;
	char	**paths;
	char	*path;
	char	*pwd;

	printf("Child gets executed \n");
	printf("trying to execute: %s\n", command);
	execve(command, argv, envp);
	pwd = msh_pwd();
	path = ft_strjoin_3(pwd, "/", command);
	free(pwd);
	printf("trying to execute in working directory: %s\n", path);
	execve(path, argv, envp);
	free(path);
	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin_3(paths[i], "/", command);
		printf("%s\n", path);
		if (execve(path, argv, envp) != -1)
			break ;
		free(path);
		i++;
	}
	printf("Command not found\n");
	mini_execve_free_paths(paths);
}

void	mini_execve(char *command, char **argv, char **envp)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		write(2, "Error: fork failed\n", 19);
	}
	if (child_pid == 0)
		mini_execve_child(command, argv, envp);
	else
	{
		wait(0);
		printf("Parent has waited for child process to end\n");
		mini_execve_free_paths(envp);
	}
}
