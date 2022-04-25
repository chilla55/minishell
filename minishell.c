/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:16:11 by skorte            #+#    #+#             */
/*   Updated: 2022/04/25 10:21:02 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_free(char *input, char *temp, char *prompt,
			t_envp_list *envp_list, char **envp);
void	msh_free_envp(char **envp);
void	msh_free_envp_list(t_envp_list *envp_list);

int	msh_parser(char *input)
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
	char		*input;
	char		*temp;
	char		*prompt;
	int			exit;
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
//		msh_parser(input);
/* If there is anything on the line, print it and remember it. */
		if (*input)
		{
			add_history (input);
			temp = ft_strdup(input);
			free (input);
			input = ft_strdelendchr(temp, ' ');
			free (temp);
			printf ("%s\n", input);
		}
/* Check for `command' "exit" */
		if (ft_strncmp(input, "exit", 5) == 0)
		{
			exit = 1;
			break ;
		}
/* Check for `command' "list" to print history */
/*	    else if (ft_strncmp(input, "list", 5) == 0)
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
		}*/
		else
		{
			mini_execve(input, argv, envp);
			free(input);
		}
	}
	clear_history();
	msh_free(input, temp, prompt, envp_list, envp);
	return (0);
}

void	msh_free(char *input, char *temp, char *prompt,
			t_envp_list *envp_list, char **envp)
{
	if (input)
		free(input);
	if (temp)
		NULL;//		free(temp);
	if(prompt)
		NULL;//		free(prompt);
	if (envp_list)
		msh_free_envp_list(envp_list);
	if (envp)
		msh_free_envp(envp);
}

void	msh_free_envp(char **envp)
{
	char		**env;

	env = envp;
	while (*env != NULL)
	{
		free(*env);
		env++;
	}
	free (envp);
}

void	msh_free_envp_list(t_envp_list *envp_list)
{
	if (envp_list)
	{
		if (envp_list->name)
			free (envp_list->name);
		if (envp_list->value)
			free (envp_list->value);
		if (envp_list->next)
			msh_free_envp_list(envp_list->next);
		free (envp_list);
	}
}
