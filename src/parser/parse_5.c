/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 23:29:20 by skorte            #+#    #+#             */
/*   Updated: 2022/06/22 13:44:13 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*dollar_parse(char *input);
static char	*handle_dollar_cases(char *output, int i, int *sq, int *dq);

char	**prepare_split_input(char *input)
{
	char	*temp;
	char	**input_split;

	temp = ft_strdup(input);
	temp = dollar_parse(temp);
	if (!check_allowed(temp))
		return (NULL);
	input_split = ft_split_parse(temp, '|');
	free(temp);
	return (input_split);
}

static char	*dollar_parse(char *input)
{
	int		quotes[2];
	int		i;
	char	*output;

	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	output = ft_strdup(input);
	while (output[i])
	{
		test_quotes(output, i, &quotes[0], &quotes[1]);
		output = handle_dollar_cases(output, i, &quotes[0], &quotes[1]);
		i++;
	}
	free(input);
	return (output);
}

static char	*handle_dollar_cases(char *output, int i, int *sq, int *dq)
{
	if (output[i] == '$' && !*sq && !*dq
		&& ft_strchr(" |\0", output[i + 1]))
	{
		if (i == 0 || (i > 0 && output[i - 1] != '$'))
		{
			output = ft_strinsertchar(output, '\'', i);
			*sq = 1;
			output = ft_strinsertchar(output, '\'', i + 2);
		}
	}
	else if (output[i] == '$' && !*sq && *dq
		&& ft_strchr("\" |\0", output[i + 1]))
	{
		if (i == 0 || (i > 0 && output[i - 1] != '$'))
		{
			output = ft_strinsertchar(output, '\"', i);
			output = ft_strinsertchar(output, '\'', i + 1);
			*sq = 1;
			output = ft_strinsertchar(output, '\'', i + 3);
			output = ft_strinsertchar(output, '\"', i + 4);
		}
	}
	return (output);
}
