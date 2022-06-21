/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:00:29 by skorte            #+#    #+#             */
/*   Updated: 2022/06/21 13:22:45 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_newline_arg(char	*str);

/*
** Your shell must implement the following builtins:
** echo with option -n
** cd with only a relative or absolute path
** pwd with no options
** export with no options
** unset with no options
** env with no options or arguments
** exit with no options
*/

// *** echo ***

void	msh_echo(char **strs)
{
	int	no_new_line;
	int	i;

	if (!strs[1])
	{
		write(1, "\n", 1);
		return ;
	}
	no_new_line = 0;
	i = 1;
	while (is_newline_arg(strs[i]))
		i++;
	if (i > 1)
		no_new_line = 1;
	while (strs[i])
	{
		write(1, strs[i], ft_strlen(strs[i]));
		if (strs[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (no_new_line == 0)
		write(1, "\n", 1);
}

static int	is_newline_arg(char	*str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}
