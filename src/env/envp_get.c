/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:43:21 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/05/05 16:50:34 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*msh_get_envp_name(char *content)
{
	char	*temp;
	char	*envp_name;
	size_t	len;

	temp = ft_strchr(content, '=');
	if (temp)
	{
		len = ft_strlen(content) - ft_strlen(temp) + 1;
		envp_name = malloc(sizeof(char) * len);
		ft_strlcpy(envp_name, content, len);
		return (envp_name);
	}
	return (NULL);
}

char	*msh_get_envp_value(t_envp_list *envp_list, char *name)
{
	t_envp_list	*envp_list_element;

	envp_list_element = envp_list;
	while (envp_list_element)
	{
		if (!ft_strncmp(envp_list_element->name, name, ft_strlen(name) + 1))
			break ;
		else
			envp_list_element = envp_list_element->next;
	}
	if (envp_list_element)
		return (envp_list_element->value);
	return (NULL);
}

t_envp_list	*msh_get_envp_ptr(t_envp_list *envp_list, char *name)
{
	t_envp_list	*envp_list_element;

	envp_list_element = envp_list;
	while (envp_list_element)
	{
		if (!ft_strncmp(envp_list_element->name, name, ft_strlen(name) + 1))
			break ;
		else
			envp_list_element = envp_list_element->next;
	}
	return (envp_list_element);
}
