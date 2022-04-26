/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:00:29 by skorte            #+#    #+#             */
/*   Updated: 2022/04/26 08:42:06 by agrotzsc         ###   ########.fr       */
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

char	*msh_pwd(void)
{
	char	*buffer;
	char	*rtn;
	int		bufferlength;

	bufferlength = 1024;
	buffer = malloc(bufferlength * sizeof(char));
	getcwd(buffer, bufferlength);
	rtn = ft_strdup(buffer);
	free(buffer);
	return (rtn);
}
