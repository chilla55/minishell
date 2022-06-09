/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 08:45:29 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/09 14:44:37 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_strinsertchar(char *str, char c, int pos);
static int	ft_find_word_end(char *temp, int i);

char	*ft_insert_pipes(char *input)
{
	char	*temp;
	int		sq;
	int		dq;
	int		i;

	sq = 0;
	dq = 0;
	i = 0;
	temp = ft_strdup(input);
	if (!ft_strncmp(temp, "<<", 2))
	{
		i = i + 2;
		temp = ft_strinsertchar(temp, ' ', i);
		i = ft_find_word_end(temp, i);
		temp = ft_strinsertchar(temp, ' ', i);
		i++;
		temp = ft_strinsertchar(temp, 's', i);
		i++;
		while (temp[i] == ' ')
			i++;
		if (temp[i])
			temp = ft_strinsertchar(temp, '|', i);
	}
	else if (temp[0] == '<' || temp[0] == '>')
		temp = ft_strjoin_frees2("echo -n \"\" ", temp);
	else if (temp[0] == '\'' && !dq)
		sq = (sq + 1) % 2;
	else if (temp[0] == '\"' && !sq)
		dq = (dq + 1) % 2;
	while (temp[i])
	{
		if (temp[i] == '\'' && !dq)
			sq = (sq + 1) % 2;
		else if (temp[i] == '\"' && !sq)
			dq = (dq + 1) % 2;
		else if ((temp[i] == '<' && temp[i + 1] == '<' && !sq && !dq)
			|| (temp[i] == '>' && temp[i + 1] == '>' && !sq && !dq))
		{
			if (temp[i - 1] == '|')
				i--;
			else
				temp = ft_strinsertchar(temp, '|', i);
			i = i + 3;
			temp = ft_strinsertchar(temp, ' ', i);
			i = ft_find_word_end(temp, i);
			while (temp[i] == ' ')
				i++;
			if (temp[i])
				temp = ft_strinsertchar(temp, '|', i);
		}
		else if ((temp[i] == '<' || temp[i] == '>') && !sq && !dq)
		{
			if (temp[i - 1] == '|')
				i--;
			else
				temp = ft_strinsertchar(temp, '|', i);
			i = i + 2;
			temp = ft_strinsertchar(temp, ' ', i);
			i = ft_find_word_end(temp, i);
			while (temp[i] == ' ')
				i++;
			if (temp[i])
				temp = ft_strinsertchar(temp, '|', i);
		}
		if (temp[i])
			i++;
	}
	return (temp);
}

void	ft_sort_redirections(char **split)
{
	int		i;
	char	*temp;

	i = 1;
	while (split[i])
	{
		if (split[i][0] == '<')
		{
			temp = split[i];
			split[i] = split[i - 1];
			split[i - 1] = temp;
		}
		i++;
	}
}

static char	*ft_strinsertchar(char *str, char c, int pos)
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

static int	ft_find_word_end(char *temp, int i)
{
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	while (temp[i] == ' ')
		i++;
	while (temp[i] != ' ' || sq || dq)
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
