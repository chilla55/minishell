/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:39:29 by skorte            #+#    #+#             */
/*   Updated: 2022/05/10 22:27:27 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	execve_extern(char *command, char **argv, char **envp);
static int	try_build_in(char *word, char **words, t_envp_list *envp_list);

int	run_command(t_exe_list *exe_list_element, t_envp_list *envp_list)
{
	if (!try_build_in(exe_list_element->command,
			exe_list_element->argv, envp_list))
		execve_extern(exe_list_element->command,
			exe_list_element->argv, msh_create_envp_from_list(envp_list));
	return (0);
}

/*
** searches the given command in current path and PATH
** and tries to execute it.
*/

static int	execve_extern(char *command, char **argv, char **envp)
{
	int		i;
	char	**paths;
	char	*path;
	char	*pwd;

	execve(command, argv, envp);
	pwd = msh_pwd();
	path = ft_strjoin_3(pwd, "/", command);
	free(pwd);
	execve(path, argv, envp);
	free(path);
	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin_3(paths[i], "/", command);
		if (execve(path, argv, envp) != -1)
			break ;
		free(path);
		i++;
	}
	write(2, &"Error: Command not found\n", 25);
	free_paths(paths);
	return (-1);
}

static int	try_build_in(char *word, char **words, t_envp_list *envp_list)
{
	if (!ft_strncmp(word, "echo", 5))
		msh_echo(words);
	else if (!ft_strncmp(word, "export", 7))
		msh_export(words, envp_list);
	else if (!ft_strncmp(word, "cd", 3))
		msh_cd(words);
	else if (!ft_strncmp(word, "unset", 6))
		msh_unset(words, envp_list);
	else if (!ft_strncmp(word, "pwd", 4))
		msh_pwd_cmd();
	else if (!ft_strncmp(word, "env", 4))
		msh_env(words, envp_list);
	else
		return (0);
	exit (0);
}
