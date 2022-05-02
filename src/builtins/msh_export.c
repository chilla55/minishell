/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 12:14:10 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/05/02 10:42:59 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		msh_print_envp_list(envp_list);
	else
		msh_export_worker(words, envp_list, 1);
}
