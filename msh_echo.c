/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:00:29 by skorte            #+#    #+#             */
/*   Updated: 2022/04/23 23:00:29 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int argc, char **argv)
{
	int	no_new_line;
	int	i;

	if (argc == 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	no_new_line = 0;
	if (ft_strncmp(argv[1], "-n", 3) == 0)
		no_new_line = 1;
	i = no_new_line + 1;
	while (i < argc)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		i++;
		if (i < argc)
			write(1, " ", 1);
	}
	if (no_new_line == 0)
		write(1, "\n", 1);
	return (0);
}
