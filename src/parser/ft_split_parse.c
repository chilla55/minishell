/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 00:56:57 by skorte            #+#    #+#             */
/*   Updated: 2021/08/21 16:00:50 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** ft_split_parse Parameters:
** #1. The string to be split.
** #2. The delimiter character.
Return value: The array of new strings resulting from the split.
NULL if the allocation fails.
External functs. malloc, free
Description: Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must be
ended by a NULL pointer.
*/

static int	ft_str_word_count(char const *s, char c)
{
	int	i[5];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	i[4] = 0;
	while (i[0] <= (int)ft_strlen(s))
	{
		if (s[i[0]] == '\'' && !i[4])
				i[3] = (i[3] + 1) % 2;
		else if (s[i[0]] == '\"' && !i[3])
				i[4] = (i[4] + 1) % 2;
		if ((s[i[0]] == c && (!i[3] || !i[4])) || s[i[0]] == '\0')
		{
			if (i[2] != 0)
				i[1]++;
			i[2] = 0;
		}
		else
			i[2]++;
		i[0]++;
	}
	return (i[1]);
}

static void	ft_str_words(char const *s, char **dest, char c)
{
	int	*i;

	i = ft_calloc(6, sizeof(int));
	while (i[0] <= (int)ft_strlen(s))
	{
		if (s[i[0]] == '\'' && !i[4])
				i[3] = (i[3] + 1) % 2;
		else if (s[i[0]] == '\"' && !i[3])
				i[4] = (i[4] + 1) % 2;
		if ((s[i[0]] == c && !i[3] && !i[4]) || s[i[0]] == '\0')
		{
			if (i[2] != 0)
			{
				dest[i[1]] = ft_substr(s, i[5], i[2]);
				i[1]++;
			}
			i[2] = 0;
			i[5] = i[0] + 1;
		}
		else
			i[2]++;
		i[0]++;
	}
	dest[i[1]] = NULL;
	free(i);
}

char	**ft_split_parse(char const *s, char c)
{
	char	**dest;
	int		n;

	if (!s)
		return (NULL);
	n = ft_str_word_count(s, c);
	dest = ft_calloc((n + 1), sizeof(char *));
	if (dest == NULL)
		return (dest);
	ft_str_words(s, dest, c);
	return (dest);
}
