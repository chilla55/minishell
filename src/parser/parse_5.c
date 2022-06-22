/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 23:29:20 by skorte            #+#    #+#             */
/*   Updated: 2022/06/22 08:56:21 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*backslash_parse(char *input);
static char	*dollar_parse(char *input);

char	**prepare_split_input(char *input)
{
	char	*temp;
	char	**input_split;

	temp = backslash_parse(input);
	temp = dollar_parse(temp);
	if (!check_allowed(temp))
		return (NULL);
	input_split = ft_split_parse(temp, '|');
	free(temp);
	return (input_split);
}

/*
static char	*backslash_parse(char *input)
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
		if (output[i] == '\\' && output[i + 1] == '\\')
			NULL;
		else if (output[i] == '\\' && !quotes[0] &&
			!quotes[1] && output[i + 1] != '\'')
		{
			output[i] = '\'';
			quotes[0] = 1;
			output = ft_strinsertchar(output, '\'', i + 2);
		}
		else if (output[i] == '\\' && !quotes[0] && quotes[1])
			output = ft_strdelchar(output, i);
		else if (output[i] == '\\' && !quotes[0] && !quotes[1]
			&& output[i + 1] == '\'')
		{
			output = ft_strdelchar(output, i);
			output[i] = 127;
		}
		i++;
	}
	return (output);
}
*/

static char	*backslash_parse(char *input)
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
		if (output[i] == '\\' && !quotes[0] && quotes[1])
		{
			if (output[i + 1] == '\\')
				output = ft_strdelchar(output, i);
		}
		else if (output[i] == '\\' && !quotes[0] && !quotes[1])
		{
			if (output[i + 1] != '\'')
			{
				output[i] = '\'';
				quotes[0] = 1;
				output = ft_strinsertchar(output, '\'', i + 2);
			}
			else
			{
				output = ft_strdelchar(output, i);
				output[i] = 127;
			}
		}
		i++;
	}
	return (output);
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
		if (output[i] == '$' && !quotes[0] && !quotes[1] && ft_strchr(" |\0", output[i + 1]))
		{
			if (i == 0 || (i > 0 && output[i - 1] != '$'))
			{
				output = ft_strinsertchar(output, '\'', i);
				quotes[0] = 1;
				output = ft_strinsertchar(output, '\'', i + 2);
			}
		}
		else if (output[i] == '$' && !quotes[0] && quotes[1] && ft_strchr("\" |\0", output[i + 1]))
		{
			if (i == 0 || (i > 0 && output[i - 1] != '$'))
			{
				output = ft_strinsertchar(output, '\"', i);
				output = ft_strinsertchar(output, '\'', i + 1);
				quotes[0] = 1;
				output = ft_strinsertchar(output, '\'', i + 3);
				output = ft_strinsertchar(output, '\"', i + 4);
			}
		}
		i++;
	}
	free(input);
	return (output);
}
