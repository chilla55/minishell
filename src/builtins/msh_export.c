/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 12:14:10 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/16 18:57:00 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	msh_print_envp_list_abc(t_envp_list *envp_list, char *last);

void	free_split(char **strarr)
{
	int	i;

	i = 0;
	while (strarr[i])
	{
		free(strarr[i]);
		i++;
	}
	free(strarr);
}

void	msh_export_worker(char	**words, t_envp_list *envp_list, int i)
{
	int			a;
	char		**split;

	split = ft_split(words[i], '=');
	a = msh_exist_envp(envp_list, split[0]);
	if (!split[1] && a == 0)
		msh_set_envp(envp_list, split[0], "", a);
	else if (split[1])
		msh_set_envp(envp_list, split[0], split[1], a);
	free_split(split);
	if (words[i + 1])
		msh_export_worker(words, envp_list, i + 1);
}

void	msh_export(char	**words, t_envp_list *envp_list)
{
	if (!words[1])
		msh_print_envp_list_abc(envp_list, NULL);
	else
		msh_export_worker(words, envp_list, 1);
}

static void	msh_print_envp_list_abc(t_envp_list *envp_list, char *last)
{
	t_envp_list	*ptr;
	char		*next;

	next = NULL;
	ptr = envp_list;
	while (ptr && ft_strncmp(ptr->name, last, ft_strlen(ptr->name)) <= 0)
		ptr = ptr->next;
	if (ptr)
		next = ptr->name;
	while (ptr)
	{
		if (ft_strncmp(ptr->name, last, ft_strlen(ptr->name)) > 0
			&& ft_strncmp(ptr->name, next, ft_strlen(ptr->name)) < 0)
			next = ptr->name;
		ptr = ptr->next;
	}
	if (!next)
		return ;
	printf("declare -x %s=%s\n", next, msh_get_envp_value(envp_list, next));
	msh_print_envp_list_abc(envp_list, next);
}
