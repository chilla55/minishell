/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:46:45 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/05/05 16:47:11 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	msh_del_envp_free(t_envp_list	*envp_l_e)
{
	free(envp_l_e->name);
	free(envp_l_e->value);
	free(envp_l_e);
}

int	msh_del_envp(t_envp_list *envp_list, char *name)
{
	t_envp_list	*envp_l_e;
	t_envp_list	*temp;

	envp_l_e = envp_list;
	if (!ft_strncmp(envp_l_e->name, name, ft_strlen(name) + 1))
	{
		envp_list = envp_l_e->next;
		msh_del_envp_free(envp_l_e);
		return (1);
	}
	while (envp_l_e->next)
	{
		if (!ft_strncmp(envp_l_e->next->name, name, ft_strlen(name) + 1))
		{
			temp = envp_l_e->next->next;
			msh_del_envp_free(envp_l_e->next);
			envp_l_e->next = temp;
			return (1);
		}
		envp_l_e = envp_l_e->next;
	}
	return (0);
}
