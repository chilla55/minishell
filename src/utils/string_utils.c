/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:43:21 by skorte            #+#    #+#             */
/*   Updated: 2022/06/21 17:12:40 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*ft_strdelchar(char *str, int pos)
{
	char	*str1;
	char	*str2;
	char	*dest;

	if (!str)
		return (NULL);
	if (pos > (int)ft_strlen(str))
		pos = ft_strlen(str);
	str1 = ft_substr(str, 0, pos);
	str2 = ft_substr(str, pos + 1, ft_strlen(str) - pos);
	dest = ft_strjoin(str1, str2);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str)
		free(str);
	return (dest);
}

char	*join_try_free(char *a, char *b)
{
	if (a && b)
		return (ft_strjoin_free(a, b));
	else if (a && !b)
		return (a);
	else if (!a && b)
		return (b);
	return (0x0);
}
