/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:00:29 by skorte            #+#    #+#             */
/*   Updated: 2022/04/26 09:09:06 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (ft_strncmp(strs[1], "-n", 3) == 0)
		no_new_line = 1;
	i = no_new_line + 1;
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
