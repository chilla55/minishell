/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:16:11 by skorte            #+#    #+#             */
/*   Updated: 2022/04/25 06:15:47 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		mini_execve(char *const input, char **argv, char **envp);

int		msh_parser(char *input)
{
	char	**split_input;
	int		i;
	int		word_start;
	int		word_len;
	int		word_count;

	split_input = malloc(sizeof(char *) * ft_strlen(input));
	i = 0;
	word_start = 0;
	word_len = 0;
	word_count = 0;
	while (i < (int)ft_strlen(input))
	{
		if (!ft_strchr(" <>|'$'", input[i]))
		{
			word_len++;
		}
		else if (ft_strchr("|'$'", input[i]))
		{
			split_input[word_count] = ft_substr(input, word_start, word_len);
			write(1, split_input[word_count], word_len);
			word_len = 1;
			word_start = i;
			word_count++;
		}
		else
			word_len++;
		i++;
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*temp;
	char	*prompt;
	int		exit;
	t_envp_list	*envp_list;
	

	if (argc != 1) // Dummy for gcc -Werror
		return (-1);
//	printf("%s\n", getenv("XYZ"));
//	setenv("XYZ", "XYZ", 1);
//	printf("%s\n", getenv("XYZ"));
//	printf("%s\n", envp[0]);
//	envp[0] = ft_strdup("XYZZ=xyzz");
//	printf("%s\n", getenv("XYZZ"));
	envp_list = msh_create_envp_list(envp);
//	msh_print_envp_list(envp_list);
//	printf("%s\n", msh_get_envp_value(envp_list, "PATH"));
	printf("%s\n", envp[0]);
	envp = msh_create_envp_from_list(envp_list);
	printf("%s\n", envp[0]);
	printf("Hello World! One day, I will be a true MiniShell...\n");
	prompt = "Try me!$ ";
	exit = 0;
	while (!exit)
    {
    	input = readline(prompt);
		msh_parser(input);
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
