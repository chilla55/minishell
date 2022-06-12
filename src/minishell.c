/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:16:11 by skorte            #+#    #+#             */
/*   Updated: 2022/06/12 15:12:42 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_free(char *input, t_envp_list *envp_list);
void	loop(char *input, char *prompt, t_envp_list *envp_list);
void	msh_free_envp_list(t_envp_list *envp_list);

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	char		*prompt;
	t_envp_list	*envp_list;

	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	input = 0x0;
	prompt = 0x0;
	signal_inter();
	envp_list = msh_create_envp_list(envp);
	msh_set_envp(envp_list, "SHELL", "minishell", 1);
	msh_set_envp(envp_list, "?", "0", 1);
	loop(input, prompt, envp_list);
	clear_history();
	return (0);
}

void	loop(char *input, char *prompt, t_envp_list *envp_list)
{
	char		*temp;

	while (1)
	{
		temp = getcwd(NULL, 0);
		prompt = ft_strjoin_3("Try me!:", temp, "$ ");
		free(temp);
		temp = readline(prompt);
		free(prompt);
		if (!temp)
			break ;
		else if (ft_strlen(temp))
		{
			add_history (temp);
			if (input)
				free(input);
			input = ft_strdelendchr(temp, ' ');
			if (ft_strncmp(input, "exit", 5) == 0)
				break ;
			msh_parser(input, envp_list);
		}
		if (temp)
			free (temp);
	}
	msh_free(input, envp_list);
}

void	msh_free(char *input, t_envp_list *envp_list)
{
	if (input)
		free(input);
	if (envp_list)
		msh_free_envp_list(envp_list);
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
