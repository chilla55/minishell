/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:29:45 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/22 12:38:09 by skorte           ###   ########.fr       */
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

int	check_allowed(char *input)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>' || input[i] == '|')
		{
			if ((input[i] == '<' && input[i + 1] == '<')
				|| (input[i] == '>' && input[i + 1] == '>'))
				i++;
			a = contains(input, i + 1, "<|>");
			if (a != 0)
				break ;
		}
		i++;
	}
	print_error(a, input);
	if (a != 0)
		free(input);
	return (a == 0);
}
