/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:21:45 by skorte            #+#    #+#             */
/*   Updated: 2022/04/25 15:27:02 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_parser(char *input, char **envp)
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
	mini_execve(words[0], words, envp);
	return (0);
}
