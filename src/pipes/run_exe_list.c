/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exe_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:26:18 by skorte            #+#    #+#             */
/*   Updated: 2022/05/12 13:49:30 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	run_exe_list(t_exe_list *exe_list, t_envp_list *envp_list,
				int fd_in, int fd_out);
static int	pipe_and_fork(int *fd_pipe);
static int	fd_duplicator(int fd_in, int fd_out);

/*
** init_exe 
** - makes backups of standard input and output.
** - starts execution of exe_list.
** - waits for the processes to finish.
** - resets standard input and output.
** - frees exe_list and envp_list.
*/

int	init_exe(t_exe_list *exe_list, t_envp_list *envp_list)
{
	int	fd_in;
	int	fd_out;
	int	pid;

	if (!exe_list)
		return (-1);
	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	run_exe_list(exe_list, envp_list, fd_in, fd_out);
	wait(&pid);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
	free_exe_list(exe_list);
	return (0);
}

/*
** run_exe_list
** - tries to run all commands in the given exe_list.
** - pipes the output of one command to the input of the next.
*/

static int	run_exe_list(t_exe_list *exe_list, t_envp_list *envp_list,
	int fd_in, int fd_out)
{
	int		fd_pipe[2];
	pid_t	child_pid;

	child_pid = pipe_and_fork(fd_pipe);
	if (!exe_list->next)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		if (!child_pid)
		{
			fd_duplicator(fd_in, fd_out);
			run_command(exe_list, envp_list);
		}
	}
	else
	{
		if (!child_pid)
		{
			fd_duplicator(fd_in, fd_pipe[1]);
			run_command(exe_list, envp_list);
		}
		else
			run_exe_list(exe_list->next, envp_list, fd_pipe[0], fd_out);
	}
	return (0);
}

/*
** sets fd_in and fd_out as standart input and output
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
** initializes pipe
** forks process
** closes unused end of pipe for child and parent process
*/

static int	pipe_and_fork(int *fd_pipe)
{
	int	child_pid;

	if (pipe(fd_pipe) == -1)
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