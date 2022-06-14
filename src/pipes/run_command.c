/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:39:29 by skorte            #+#    #+#             */
/*   Updated: 2022/06/14 20:25:11 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	execve_extern(char *command, char **argv, char **envp,
				t_envp_list *envp_list);
static int	try_build_in(char *word, char **words, t_envp_list *envp_list);

int	run_command(t_exe_list *exe_list_element, t_envp_list *envp_list)
{
	char	**envp;

	if (!try_build_in(exe_list_element->command,
			exe_list_element->argv, envp_list))
	{
		envp = msh_create_envp_from_list(envp_list);
		execve_extern(exe_list_element->command, exe_list_element->argv,
			envp, envp_list);
		free_split(envp);
	}
	return (0);
}

/*
** searches the given command in current path and PATH
** and tries to execute it.
*/

static int	execve_extern(char *command, char **argv, char **envp,
				t_envp_list *envp_list)
{
	int		i;
	char	**paths;
	char	*path;

	execve(command, argv, envp);
	path = ft_strjoin_frees1(msh_pwd(), "/");
	path = ft_strjoin_frees1(path, command);
	execve(path, argv, envp);
	free(path);
	paths = ft_split(msh_get_envp_value(envp_list, "PATH"), ':');
	i = 0;
	if (paths)
	{
		while (paths[i])
		{
			path = ft_strjoin_3(paths[i], "/", command);
			if (execve(path, argv, envp) != -1)
				break ;
			free(path);
			i++;
		}
		free_paths(paths);
	}
	write(2, command, ft_strlen(command));
	write(2, &": Command not found\n", 20);
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
	else if (!ft_strncmp(word, ">>", 2))
		msh_redirect_to_file(words[1], 1);
	else if (!ft_strncmp(word, ">", 1))
		msh_redirect_to_file(words[1], 0);
	else if (!ft_strncmp(word, "<<", 3))
		msh_read_input_till_delimiter(words[1], envp_list);
	else if (!ft_strncmp(word, "<", 2))
		msh_read_from_file(words[1]);
	else
		return (0);
	return (1);
}

int	run_export(t_exe_list *exe_list, t_envp_list *envp_list,
	int fd_in, int fd_out)
{
	if (!exe_list)
		return (1);
	if (!ft_strncmp(exe_list->command, "export", 7) && !exe_list->next)
	{
		msh_export(exe_list->argv, envp_list);
		if (exe_list->next)
			run_exe_list(exe_list->next, envp_list, fd_in, fd_out);
		return (1);
	}	
	else if (!ft_strncmp(exe_list->command, "unset", 6) && !exe_list->next)
	{
		msh_unset(exe_list->argv, envp_list);
		if (exe_list->next)
			run_exe_list(exe_list->next, envp_list, fd_in, fd_out);
		return (1);
	}	
	else if (!ft_strncmp(exe_list->command, "cd", 6) && !exe_list->next)
	{
		msh_cd(exe_list->argv);
		if (exe_list->next)
			run_exe_list(exe_list->next, envp_list, fd_in, fd_out);
		return (1);
	}	
	return (0);
}
