/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:00:29 by skorte            #+#    #+#             */
/*   Updated: 2022/04/25 07:01:26 by skorte           ###   ########.fr       */
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

int	main(void)
{
	char	*buffer;
	int		bufferlength;

	bufferlength = 128; // put that one into the header???
	buffer = malloc(bufferlength * sizeof(char));
	getcwd(buffer, bufferlength);
	printf("%s\n", buffer);
	free(buffer);
	return (0);
}
