/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:16:11 by skorte            #+#    #+#             */
/*   Updated: 2022/06/22 15:32:53 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_free(char *input, t_envp_list *envp_list, char *temp);
void	loop(char **input, char *prompt, t_envp_list *envp_list, char **temp);
void	msh_free_envp_list(t_envp_list *envp_list);
char	*create_prompt(t_envp_list *envp_list);

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	char		*prompt;
	char		*temp;
	t_envp_list	*envp_list;

	(void)argc;
	(void)argv;
	input = 0x0;
	prompt = 0x0;
	temp = 0x0;
	signal_inter();
	envp_list = msh_create_envp_list(envp);
	msh_set_envp(envp_list, "SHELL", "minishell", 1);
	msh_set_envp(envp_list, "?", "0", 1);
	loop(&input, prompt, envp_list, &temp);
	msh_free(input, envp_list, temp);
	clear_history();
	return (0);
}

void	loop(char **input, char *prompt, t_envp_list *envp_list, char **temp)
{
	int	i;

	free_str(*temp);
	prompt = create_prompt(envp_list);
	*temp = readline(prompt);
	free(prompt);
	if (!*temp)
		return ;
	else if (!ft_strlen(*temp))
		return (loop(input, prompt, envp_list, temp));
	add_history (*temp);
	free_str(*input);
	*input = ft_strdelendchr(*temp, ' ');
	if (ft_strncmp(*input, "exit", 5) == 0)
		return ;
	i = msh_parser(*input, envp_list);
	if (i == 2)
	{
		msh_free(*input, envp_list, *temp);
		clear_history();
		exit(127);
	}
	else if (i == 1)
		return ;
	loop(input, prompt, envp_list, temp);
}

void	msh_free(char *input, t_envp_list *envp_list, char *temp)
{
	if (input)
		free(input);
	if (envp_list)
		msh_free_envp_list(envp_list);
	if (temp)
		free (temp);
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

char	*create_prompt(t_envp_list *envp_list)
{
	char	*prompt;
	char	*cwd;
	char	*user;
	char	*shell;

	user = ft_strdup(msh_get_envp_value(envp_list, "USER"));
	shell = ft_strdup(msh_get_envp_value(envp_list, "SHELL"));
	cwd = getcwd(NULL, 0);
	if (!user)
		prompt = ft_strdup("@");
	else
		prompt = ft_strjoin(user, "@");
	prompt = ft_strjoin_frees1(prompt, shell);
	prompt = ft_strjoin_frees1(prompt, ":");
	prompt = ft_strjoin_frees1(prompt, cwd);
	prompt = ft_strjoin_frees1(prompt, "$ ");
	if (user)
		free(user);
	if (shell)
		free(shell);
	if (cwd)
		free(cwd);
	return (prompt);
}
