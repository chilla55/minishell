/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:40:45 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/05/05 16:41:58 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envp_list	*msh_create_envp_list(char **envp)
{
	char		**env;
	t_envp_list	*envp_list;
	t_envp_list	*envp_list_element;

	env = envp;
	envp_list = msh_envp_lstnew(*env);
	envp_list_element = envp_list;
	env++;
	while (*env != 0)
	{
		envp_list_element->next = msh_envp_lstnew(*env);
		envp_list_element = envp_list_element->next;
		env++;
	}
	return (envp_list);
}

t_envp_list	*msh_copy_envp_list(t_envp_list *old_envp_list)
{
	t_envp_list	*new_envp_list;
	t_envp_list	*tmp;
	t_envp_list	*envp_list_element;

	tmp = old_envp_list;
	new_envp_list = msh_envp_lstnew_2(tmp->name, tmp->value);
	envp_list_element = new_envp_list;
	tmp = tmp->next;
	while (tmp)
	{
		envp_list_element->next = msh_envp_lstnew_2(tmp->name, tmp->value);
		envp_list_element = envp_list_element->next;
		tmp = tmp->next;
	}
	return (new_envp_list);
}

char	**msh_create_envp_from_list(t_envp_list *envp_list)
{
	char		**rtn;
	t_envp_list	*envp_list_element;
	int			i;
	int			lstsize;

	envp_list_element = envp_list->next;
	lstsize = msh_envp_lstsize(envp_list_element);
	rtn = malloc (sizeof(char *) * (lstsize + 1));
	i = 0;
	while (envp_list_element)
	{
		rtn[i] = ft_strjoin_3(envp_list_element->name,
				"=", envp_list_element->value);
		envp_list_element = envp_list_element->next;
		i++;
	}
	rtn[i] = NULL;
	return (rtn);
}
