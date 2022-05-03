/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:21:45 by skorte            #+#    #+#             */
/*   Updated: 2022/05/03 08:06:32 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	msh_try_build_in(char *word, char **words, t_envp_list *envp_list)
{
	printf("Searching for %s in built-ins\n", words[0]);
	if (!ft_strncmp(word, "echo", 5))
	{
		msh_echo(words);
		return (1);
	}
	else if (!ft_strncmp(word, "export", 7))
	{
		msh_export(words, envp_list);
		return (1);
	}
	else if (!ft_strncmp(word, "cd", 3))
	{
		msh_cd(words);
		return (1);
	}
	else if (!ft_strncmp(word, "unset", 6))
	{
		msh_unset(words, envp_list);
		return (1);
	}
	else if (!ft_strncmp(word, "pwd", 4))
	{
		msh_pwd_cmd();
		return (1);
	}
	printf("%s not built-in\n", words[0]);
	msh_envp_lstsize(envp_list);
	return (0);
}

void	free_str(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

int	msh_parser(char *input, t_envp_list *envp_list)
{
	char	**words;
	int		i;
	int		word_start;
	int		word_len;
	int		word_count;
	int		single_ticks;
	int		double_ticks;

	printf("parser started\n");
	words = malloc(sizeof(char *) * ft_strlen(input));
	i = 0;
	word_start = 0;
	word_len = 0;
	word_count = 0;
	single_ticks = 0;
	double_ticks = 0;
	while (i < (int)ft_strlen(input) && ft_strchr(" ", input[i]))
	{
		word_start++;
		i++;
	}
	while (i < (int)ft_strlen(input) + 1)
	{
		if (input[i] && !ft_strchr(" <>|", input[i]))
		{
			word_len++;
			if (input[i] == '\'')
				single_ticks = (single_ticks + 1) % 2;
			if (input[i] == '\"')
				double_ticks = (double_ticks + 1) % 2;
		}			
		else if ((input[i] == ' ' && !single_ticks && !double_ticks)
				|| input[i] == '\0')
		{
			if (word_len)
			{
				words[word_count] = ft_substr(input, word_start, word_len);
				printf("%i-%p-%s|\n", word_count, words[word_count], words[word_count]);
				word_count++;
			}
			word_len = 0;
			word_start = i + 1;
		}
		else
		{
			word_len++;
		}
		i++;
	}
	words[word_count] = NULL;
	if (!msh_try_build_in(words[0], words, envp_list))
		mini_execve(words[0], words, msh_create_envp_from_list(envp_list));
	free_str(words);
	return (0);
}
