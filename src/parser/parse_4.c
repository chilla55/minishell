/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:29:45 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/22 13:58:05 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	contains(char *input, int start, char *schar)
{
	int	i;

	i = 0;
	if (!input[start])
		return (-1);
	while (input[start])
	{
		if (ft_isalnum(input[start]))
			return (0);
		while (schar[i])
		{
			if (input[start] == schar[i])
				return (start);
			i++;
		}
		i = 0;
		start++;
	}
	return (0);
}

void	print_error(int a, char *input)
{
	if (a > 0)
	{
		write(2, &"Error: Unexpected Symbol: \'", 27);
		write(2, &input[a], 1);
		write(2, &"\'\n", 2);
	}
	else if (a == -1)
		write(2, &"Error: Unexpected Symbol: \'newline\'\n", 36);
}

/*
** i[0] = index
** i[1] = contains
** i[2] = squotes
** i[3] = dquotes
*/

int	check_allowed(char *input)
{
	int	i[4];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	while (input[i[0]])
	{
		test_quotes(input, i[0], &i[2], &i[3]);
		if ((input[i[0]] == '<' || input[i[0]] == '>' || input[i[0]] == '|')
			&& !i[2] && !i[3])
		{
			if ((input[i[0]] == '<' && input[i[0] + 1] == '<')
				|| (input[i[0]] == '>' && input[i[0] + 1] == '>'))
				i[0]++;
			i[1] = contains(input, i[0] + 1, "<|>");
			if (i[1] != 0)
				break ;
		}
		i[0]++;
	}
	print_error(i[1], input);
	if (i[1] != 0)
		free(input);
	return (i[1] == 0);
}
