/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:45:08 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/05/05 16:45:36 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	msh_set_envp(t_envp_list *envp_list, char *name, char *value, int overwrite)
{
	t_envp_list	*envp_list_element;
	char		*temp;

	envp_list_element = msh_get_envp_ptr(envp_list, name);
	if (!envp_list_element)
	{
		envp_list_element = envp_list;
		while (envp_list_element->next)
			envp_list_element = envp_list_element->next;
		envp_list_element->next = msh_envp_lstnew_2(name, value);
	}
	else if (overwrite)
	{
		free(envp_list_element->value);
		envp_list_element->value = ft_strdup(value);
	}
	else
	{
		temp = strdup(envp_list_element->value);
		free(envp_list_element->value);
		envp_list_element->value = ft_strjoin_3(temp, ":", value);
		free(temp);
	}
	return (0);
}
