/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 06:15:28 by skorte            #+#    #+#             */
/*   Updated: 2022/04/25 19:45:40 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp_list	*msh_create_envp_list(char **envp)
{
	char		**env;
	t_envp_list	*envp_list;
	t_envp_list	*envp_list_element;

	env = envp;
	envp_list = msh_envp_lstnew("a=a");//*env);
	envp_list_element = envp_list;
//	env++;
	while (*env != 0)
	{
		envp_list_element->next = msh_envp_lstnew(*env);
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

int		msh_set_envp(t_envp_list *envp_list, char *name, char *value, int overwrite)
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

int	msh_del_envp(t_envp_list *envp_list, char *name)
{
	t_envp_list	*envp_list_element;
	t_envp_list *temp;

	envp_list_element = msh_get_envp_ptr(envp_list, name);
	if (!envp_list_element)
		return (-1);
	else if (!envp_list_element->next)
		NULL;
	else
	{
		temp = envp_list_element->next;
		free(envp_list_element->value);
		envp_list_element->value = ft_strdup(envp_list_element->next->value);
		free(envp_list_element->name);
		envp_list_element->value = ft_strdup(envp_list_element->next->name);
		envp_list_element->next = envp_list_element->next->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
	return (0);
}


/*int		msh_add_envp(t_envp_list envp_list, char *content)
{
	return (0);
}*/
