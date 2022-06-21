/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:22:09 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/21 09:10:15 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_first_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	**export_str_split(char *str, char c)
{
	char	**dest;
	int		s;
	int		a;

	dest = ft_calloc((3), sizeof(char *));
	s = get_first_c(str, c);
	a = ft_strlen(str);
	dest[0] = ft_substr(str, 0, s);
	if (s != a)
		dest[1] = ft_substr(str, s + 1, a);
	return (dest);
}

int	str_contains_str(char *str, char *contains)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (str[i])
	{
		while (contains[a])
		{
			if (str[i] == contains[a])
				return (1);
			a++;
		}
		i++;
	}
	return (0);
}
