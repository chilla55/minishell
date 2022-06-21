/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3_redirections_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:24:12 by skorte            #+#    #+#             */
/*   Updated: 2022/06/21 15:43:58 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*insert_space_after_redir(char *input)
{
	int		i;
	int		sq;
	int		dq;
	char	*output;

	sq = 0;
	dq = 0;
	i = 0;
	if (!input)
		return (NULL);
	output = ft_strdup(input);
	while (output[i])
	{
		test_quotes(output, i, &sq, &dq);
		if (output[i] == output[i + 1])
			NULL;
		else if (ft_strchr("<>", output[i]) && !sq && !dq)
			output = ft_strinsertchar(output, ' ', i + 1);
		i++;
	}
	return (output);
}

/*
** Returns the index of the next word's end in string temp following index i.
*/

int	find_word_end(char *temp, int i)
{
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	if (temp[i + 1] == temp[i])
		i++;
	i++;
	while (temp[i] == ' ')
		i++;
	while (!ft_strchr(" <>\0", temp[i]) || sq || dq)
	{
		if (temp[i] == '\0')
			break ;
		else if (temp[i] == '\'' && !dq)
			sq = (sq + 1) % 2;
		else if (temp[i] == '\"' && !sq)
			dq = (dq + 1) % 2;
		i++;
	}
	return (i);
}

/*
** Replace empty commands by: echo -n ""
** This command does not do anything.
*/

char	*check_if_command(char *input)
{
	int	i;

	i = 0;
	if (input)
	{
		while (input[i] == ' ')
			i++;
		if (input[i] != '\0')
			return (input);
	}
	free(input);
	return (ft_strdup("echo -n \"\""));
}

void	test_quotes(char *str, int i, int	*sq, int *dq)
{
	if (str[i] == '\'' && !*dq)
		*sq = (*sq + 1) % 2;
	else if (str[i] == '\"' && !*sq)
		*dq = (*dq + 1) % 2;
}
