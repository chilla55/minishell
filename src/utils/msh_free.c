/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:48:32 by skorte            #+#    #+#             */
/*   Updated: 2022/06/15 11:44:29 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	free_exe_list(t_exe_list *exe_list)
{
	t_exe_list	*ptr;
	int			i;

	ptr = exe_list;
	if (!exe_list)
		return ;
	if (ptr->next)
		free_exe_list(ptr->next);
	free(ptr->command);
	i = 0;
	while (ptr->argv[i])
	{
		free(ptr->argv[i]);
		i++;
	}
	free(ptr->argv);
	free(ptr);
}

void	free_str(char *str)
{
	if (str)
		free(str);
}
