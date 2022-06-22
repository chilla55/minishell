/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:10:16 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/22 13:18:37 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	msh_cd(char **argv, t_envp_list *envp_list)
{
	if (!argv[1])
		return ;
	if (chdir(argv[1]) == -1)
	{
		perror("Error");
		msh_set_envp(envp_list, "?", "1", 1);
	}
}
