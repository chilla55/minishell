/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:16:11 by skorte            #+#    #+#             */
/*   Updated: 2022/04/22 08:04:15 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		mini_execve(char *const input, char **argv, char **envp);

int main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*temp;
	char	*prompt;
	int		exit;

	printf("Hello World! One day, I will be a true MiniShell...\n");
	prompt = "Try me!$ ";
	exit = 0;
	while (!exit)
    {
    	input = readline(prompt);
    	/* If there is anything on the line, print it and remember it. */
    	if (*input)
		{
			printf ("%s\n", input);
			add_history (input);
		}
    	/* Check for `command' "exit" */
    	if (ft_strncmp(input, "exit", 5) == 0)
		{
			exit = 1;
			break;
		}
    	/* Check for `command' "list" to print history */
	    else if (ft_strncmp(input, "list", 5) == 0)
		{
			HIST_ENTRY **list;
			register int i;
			list = history_list ();
			i = 0;
			if (list)
				while(list[i])
				{
					printf ("%d: %s\n", i, list[i]->line);
					i++;
				}
			break;
		}
		else
		{
			temp = ft_strjoin("/", input);
			mini_execve(temp, argv, envp);
			free(temp);
//			printf("PATH = %s\n", getenv("PATH"));
	    	free (input);
		}
	}
	clear_history();
	return (0);
}

static void		mini_execve(char *command, char **argv, char **envp)
{
	char	**paths;
	char	*path;
	pid_t	child_pid;
	int 	i;

	path = NULL;
	child_pid = fork();
	if (child_pid == -1)
	{
		write(2, "Error: fork failed\n", 19);
	}
	if (child_pid == 0)
	{
		printf("Child gets executed\n");
		paths = ft_split(getenv("PATH"),':'); // needs to be freed!!
		i = 0;
		while (paths[i])
		{
			path = ft_strjoin(paths[i], command); // needs to be freed!!
			printf("%s\n", path);
			if (execve(path, argv, envp) != -1)
				break;
			i++;
		}
		if (!paths[i])
			printf("Command not found\n");
		i = 0;
	}
	else
	{
		wait(0);
		printf("Parent has waited for child process to end\n");
	}
}
