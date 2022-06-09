/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:54:40 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/09 13:34:32 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*msh_env_worker(char **words, t_envp_list *envp_list, int i)
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
	if (words[i + 2])
		return (msh_env_worker(words, envp_list, i + 1));
	return (words[i + 1]);
}

void	msh_env(char **words, t_envp_list *envp_list)
{
	t_envp_list	*new_envp_l;
	t_exe_list	*entry;

	if (!words[1])
	{
		msh_print_envp_list(envp_list);
		return ;
	}
	new_envp_l = msh_copy_envp_list(envp_list);
	entry = ft_calloc(1, sizeof(t_exe_list));
	entry->argv = ft_calloc(2, sizeof(char *));
	if (words[2])
		entry->argv[0] = ft_strdup(msh_env_worker(words, new_envp_l, 1));
	else
		entry->argv[0] = ft_strdup(words[1]);
	entry->command = ft_strdup(entry->argv[0]);
	init_exe(entry, new_envp_l);
	msh_free_envp_list(new_envp_l);
}
