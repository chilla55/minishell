/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 06:15:28 by skorte            #+#    #+#             */
/*   Updated: 2022/05/03 13:01:15 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"




/*
char	*msh_get_envp_ptr(t_envp_list *envp_list, char *name)
{
	t_envp_list	*envp_list_element;

	envp_list_element = envp_list;	
	if (!ft_strncmp(envp_list_element->name, name, ft_strlen(name) + 1))
		return (envp_list_element);
	while (envp_list_element->next)
	{
		if (!ft_strncmp(envp_list_element->next->name, name, ft_strlen(name) + 1))
			break;
		else
			envp_list_element = envp_list_element->next;
	}
	//if (envp_list_element)
	//	return (envp_list_element->value);
	return (&envp_list_element);
}
*/


/*int		msh_add_envp(t_envp_list envp_list, char *content)
{
	return (0);
}*/

