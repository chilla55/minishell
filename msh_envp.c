/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 06:15:28 by skorte            #+#    #+#             */
/*   Updated: 2022/04/25 06:59:29 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp_list	*msh_create_envp_list(char **envp)
{
	char		**env;
	t_envp_list	*envp_list;
	t_envp_list	*envp_list_element;

	env = envp;
	envp_list = ft_envp_lstnew(*env);
	envp_list_element = envp_list;
	env++;
	while (*env != 0)
	{
		envp_list_element->next = ft_envp_lstnew(*env);
		envp_list_element = envp_list_element->next;
		env++;
	}
	return (envp_list);
}

char	**msh_create_envp_from_list(t_envp_list *envp_list)
{
	char		**rtn;
	t_envp_list	*envp_list_element;
	int			i;
	int			lstsize;

	envp_list_element = envp_list;
	lstsize = msh_envp_lstsize(envp_list);
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

t_envp_list	*ft_envp_lstnew(char *content)
{
	t_envp_list	*rtn;

	rtn = (t_envp_list *)malloc(sizeof(t_envp_list));
	if (!rtn)
		return (rtn = NULL);
	rtn->next = NULL;
	rtn->name = msh_get_envp_name(content);
	rtn->value = ft_strdup(ft_strchr(content, '=') + 1);
	return (rtn);
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

/*int		msh_set_envp(t_list envp_list, char *content, int overwrite)
{
	t_envp_list	*envp_list_element;

	envp_list_element = envp_list;
	char	*param_2;
	t_list	*envp_list_element;

	param_2 = ft_strjoin(param, "=");
	envp_list_element = envp_list;
		return (0);
}*/

/*int		msh_add_envp(t_envp_list envp_list, char *content)
{
	return (0);
}*/
