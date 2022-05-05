/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_lst_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:42:49 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/05/05 16:42:58 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envp_list	*msh_envp_lstnew(char *content)
{
	t_envp_list	*rtn;

	rtn = (t_envp_list *)malloc(sizeof(t_envp_list));
	if (!rtn)
		return (NULL);
	rtn->next = NULL;
	rtn->name = msh_get_envp_name(content);
	rtn->value = ft_strdup(ft_strchr(content, '=') + 1);
	return (rtn);
}

t_envp_list	*msh_envp_lstnew_2(char *name, char *value)
{
	t_envp_list	*rtn;

	rtn = (t_envp_list *)malloc(sizeof(t_envp_list));
	if (!rtn)
		return (NULL);
	rtn->next = NULL;
	rtn->name = ft_strdup(name);
	rtn->value = ft_strdup(value);
	return (rtn);
}
