/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3_redirections_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:24:12 by skorte            #+#    #+#             */
/*   Updated: 2022/06/21 01:32:32 by skorte           ###   ########.fr       */
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
		if (output[i] == '\'' && !dq)
			sq = (sq + 1) % 2;
		else if (output[i] == '\"' && !sq)
			dq = (dq + 1) % 2;
		else if (output[i] == output[i + 1])
			NULL;
		else if (ft_strchr("<>", output[i]))
			output = ft_strinsertchar(output, ' ', i + 1);
		i++;
	}
	return (output);
}

/*
** Inserts char 'c' at position pos into string str.
**
** Frees the original string str. Allocates memory for the return string.
** So str = ft_strinsertchar(str, c, i) does not cause memory leaks.
*/

char	*ft_strinsertchar(char *str, char c, int pos)
{
	char	*str1;
	char	*str2;
	char	*c_str;
	char	*dest;

	if (!str)
		return (NULL);
	if (pos > (int)ft_strlen(str))
		pos = ft_strlen(str);
	str1 = ft_substr(str, 0, pos);
	str2 = ft_substr(str, pos, ft_strlen(str) - pos);
	c_str = malloc(2 * sizeof(char));
	c_str[0] = c;
	c_str[1] = '\0';
	dest = ft_strjoin_3(str1, c_str, str2);
	free(c_str);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str)
		free(str);
	return (dest);
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

void	test_quotes(char c, int	*sq, int *dq)
{
	if (c == '\'' && !*dq)
		*sq = (*sq + 1) % 2;
	else if (c == '\"' && !*sq)
		*dq = (*dq + 1) % 2;
}
