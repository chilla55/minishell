/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exe_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:26:18 by skorte            #+#    #+#             */
/*   Updated: 2022/06/08 20:52:26 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	pipe_and_fork(int *fd_pipe, int fd_in, int fd_out,
				t_exe_list *exe_list);
static int	fd_duplicator(int fd_in, int fd_out);
static void	run_exe_extend(int fd_in, int fd_out,
				t_exe_list *exe_list, t_envp_list *envp_list);

/*
* init_exe 
* - makes backups of standard input and output.
* - starts execution of exe_list.
* - waits for the processes to finish.
* - resets standard input and output.
* - frees exe_list and envp_list.
*/

int	init_exe(t_exe_list *exe_list, t_envp_list *envp_list)
{
	int		fd_in;
	int		fd_out;
	char	*stdout_envp[3];

	if (!exe_list)
		return (-1);
	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	stdout_envp[0] = ft_strdup("export");
	stdout_envp[1] = ft_strjoin_frees2("STDOUT_BACKUP=", ft_itoa(fd_out));
	stdout_envp[2] = NULL;
	msh_export(stdout_envp, envp_list);
	free(stdout_envp[0]);
	free(stdout_envp[1]);
	run_exe_list(exe_list, envp_list, fd_in, fd_out);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
	free_exe_list(exe_list);
	return (0);
}

/*
* run_exe_extend
* - extend function for run_exe_list.
*/

static void	run_exe_extend(int fd_in, int fd_out,
			t_exe_list *exe_list, t_envp_list *envp_list)
{
	fd_duplicator(fd_in, fd_out);
	run_command(exe_list, envp_list);
}

/*
* run_exe_list
* - tries to run all commands in the given exe_list.
* - pipes the output of one command to the input of the next.
*/

int	run_exe_list(t_exe_list *exe_list, t_envp_list *envp_list,
	int fd_in, int fd_out)
{
	int		fd_pipe[2];
	pid_t	child_pid;
	int		status;

	if (!exe_list)
		return (0);
	if (!run_export(exe_list, envp_list, fd_in, fd_out))
	{		
		child_pid = pipe_and_fork(fd_pipe, fd_in, fd_out, exe_list);
		if (child_pid == 0)
			run_exe_extend(fd_in, fd_pipe[1], exe_list, envp_list);
		else if (exe_list->next)
			run_exe_list(exe_list->next, envp_list, fd_pipe[0], fd_out);
		else
			close(fd_pipe[0]);
		if (waitpid(child_pid, &status, 0) > -1)
		{
			if (status != 0 || !exe_list->next)
				msh_set_envp_free_value(envp_list, "?", ft_itoa(status), 1);
		}
	}	
	return (0);
}

/*
* sets fd_in and fd_out as standart input and output
*/

static int	fd_duplicator(int fd_in, int fd_out)
{
	if (dup2(fd_in, STDIN_FILENO) < 0 || dup2(fd_out, STDOUT_FILENO) < 0)
	{
		write(2, &"Error: fd duplication failed\n", 29);
		return (-1);
	}
	return (0);
}

/*
* copies fd_in/fd_out to fd_pipe if no next command, inits pipe otherwise
* forks process,
* closes unused end of pipe for child and parent process,
*/

static int	pipe_and_fork(int *fd_pipe, int fd_in, int fd_out,
				t_exe_list *exe_list)
{
	int	child_pid;

	if (!exe_list->next)
	{
		fd_pipe[0] = dup(fd_in);
		fd_pipe[1] = dup(fd_out);
	}
	else if (pipe(fd_pipe) == -1)
		write(2, "Error: pipe failed\n", 19);
	child_pid = fork();
	if (child_pid == -1)
		write(2, "Error: fork failed\n", 19);
	else if (!child_pid)
		close(fd_pipe[0]);
	else
		close(fd_pipe[1]);
	return (child_pid);
}
