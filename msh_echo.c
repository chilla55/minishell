/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:00:29 by skorte            #+#    #+#             */
/*   Updated: 2022/04/22 12:30:53 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

int main(int argc, char **argv)
{
	int	newline;
//	int	i;

//	i = 0
	if (argc == 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	if (ft_strncmp(argv[1], "-n", 3))
		newline = 0;
	else
		newline = 1;
//	while (i < argc)
//	{
//		if (ft_strncmp(argv[i], "-n", 3)
//		{
//			newline = 0;	
//		}
//	}

//	bufferlength = 128; // put that one into the header???
//	buffer = malloc(bufferlength * sizeof(char));
//	getcwd(buffer, bufferlength);
	printf("%i\n", newline);
//	free(buffer);
	return (0);
}