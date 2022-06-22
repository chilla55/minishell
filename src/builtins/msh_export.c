/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 12:14:10 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/22 13:18:32 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	msh_print_envp_list_abc(t_envp_list *envp_list, char *last);
static int	msh_check_export_parameter(char *words);

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

	if (msh_check_export_parameter(words[i]))
	{
		split = export_str_split(words[i], '=');
		if (split[0])
		{
			a = msh_exist_envp(envp_list, split[0]);
			if (!split[1] && a == 0)
				msh_set_envp(envp_list, split[0], "", a);
			else if (split[1])
				msh_set_envp(envp_list, split[0], split[1], a);
		}
		if (split)
			free_split(split);
	}
	else
		msh_set_envp(envp_list, "?", "1", 1);
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
	printf("declare -x %s=\"%s\"\n", next, msh_get_envp_value(envp_list, next));
	msh_print_envp_list_abc(envp_list, next);
}

static int	msh_check_export_parameter(char *words)
{
	if (words[0] && !ft_isdigit(words[0]) && str_contains_str(words,
			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQESRUVWXYZ1234567890_"))
		return (1);
	write(2, &"Error: ", 7);
	write(2, words, ft_strlen(words));
	write(2, &" not a valid identifier\n", 24);
	return (0);
}
