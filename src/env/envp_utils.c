/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:45:56 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/05/05 16:46:37 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	msh_exist_envp(t_envp_list *envp_list, char *name)
{
	t_envp_list	*envp_list_element;

	envp_list_element = envp_list;
	while (envp_list_element)
	{
		if (!ft_strncmp(envp_list_element->name, name, ft_strlen(name) + 1))
			return (1);
		envp_list_element = envp_list_element->next;
	}
	return (0);
}

int	msh_envp_lstsize(t_envp_list *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	msh_print_envp_list(t_envp_list *envp_list)
{
	t_envp_list	*envp_list_element;

	envp_list_element = envp_list;
	while (envp_list_element)
	{
		printf("%s=%s\n", envp_list_element->name, envp_list_element->value);
		envp_list_element = envp_list_element->next;
	}
	return (0);
}
