/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:16:11 by skorte            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/19 15:56:24 by skorte           ###   ########.fr       */
=======
/*   Updated: 2022/05/19 10:40:30 by agrotzsc         ###   ########.fr       */
>>>>>>> e2b36db8af0a456fe42b2eded23b5a001220818f
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
	input = 0x0;
	prompt = 0x0;
	init_signal();
	envp_list = msh_create_envp_list(envp);
	msh_set_envp(envp_list, "SHELL", "minishell", 1);
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
		else if (!ft_strlen(temp))
			NULL ;
		else
		{
			add_history (temp);
			input = ft_strdelendchr(temp, ' ');
			free (temp);
			if (ft_strncmp(input, "exit", 5) == 0)
				break ;
			msh_parser(input, envp_list);
			free(input);
		}
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
