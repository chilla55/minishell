/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 08:45:29 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/09 15:33:05 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*insert_here(char *temp, int *i_0);
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
	if (temp[0] == '<' || temp[0] == '>')
		temp = ft_strjoin_frees2("echo -n \"\" ", temp);
	while (temp[i])
	{
		if (temp[i] == '\'' && !dq)
			sq = (sq + 1) % 2;
		else if (temp[i] == '\"' && !sq)
			dq = (dq + 1) % 2;
		else if ((temp[i] == '<' || temp[i] == '>') && !sq && !dq)
			temp = insert_here(temp, &i);
		if (temp[i])
			i++;
	}
	printf("%s\n", temp);
	return (temp);
}

char	*insert_here(char *temp, int *i_0)
{
	int	i;

	i = *i_0;
	if (i > 0)
	{
		if (temp[i - 1] == '|')
			i--;
		else
			temp = ft_strinsertchar(temp, '|', i);
	}
	if (temp[i + 2] == temp[i + 1])
		i++;
	i = i + 2;
	temp = ft_strinsertchar(temp, ' ', i);
	i = ft_find_word_end(temp, i);
	while (temp[i] == ' ')
		i++;
	if (temp[i] && temp[i] != '|')
		temp = ft_strinsertchar(temp, '|', i);
	*i_0 = i;
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
