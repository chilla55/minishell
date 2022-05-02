/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:16:11 by skorte            #+#    #+#             */
/*   Updated: 2022/05/02 10:57:12 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_free(char *input, char *prompt,
			t_envp_list *envp_list, char **envp);
void	msh_free_envp(char **envp);
void	msh_free_envp_list(t_envp_list *envp_list);

int main(int argc, char **argv, char **envp)
{
	char		*input;
	char		*temp;
	char		*prompt;
	int			exit;
	t_envp_list	*envp_list;

	if (argc != 1) // Dummy for gcc -Werror
		return (-1);
	if (argv[1]) // Dummy for gcc -Werror
		return (-1);
	init_signal();
	envp_list = msh_create_envp_list(envp);
	msh_set_envp(envp_list, "SHEL", "biba", 0);
	msh_set_envp(envp_list, "SHELL", "biba", 1);
	msh_print_envp_list(envp_list);
	printf("%s\n", msh_get_envp_value(envp_list, "SHELL"));
	printf("%s\n", envp[0]);
	envp = msh_create_envp_from_list(envp_list);
	printf("%s\n", envp[0]);
	
	printf("Hello World! One day, I will be a true MiniShell...\n");
	exit = 0;
	while (!exit)
	{
		temp = getcwd(NULL, 0);
		prompt = ft_strjoin_3("Try me!:", temp, "$ ");
		free(temp);
		temp = readline(prompt);
		free(prompt);
		if (!temp)
			break ;
		else if (!ft_strlen(temp))
			NULL ;
		else
		{
			add_history (temp);
			input = ft_strdelendchr(temp, ' ');
			free (temp);
			if (ft_strncmp(input, "exit", 5) == 0)
			{
				exit = 1;
				break ;
			}
			else
			{
				msh_parser(input, envp_list);
				free(input);
			}
		}
	}
	clear_history();
	msh_free(input, prompt, envp_list, envp);
	return (0);
}

void	msh_free(char *input, char *prompt,
			t_envp_list *envp_list, char **envp)
{
	if (input)
		free(input);
	if (prompt)
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
