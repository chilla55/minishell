/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 07:19:41 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/05/03 07:46:22 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	msh_unset_worker(t_envp_list *t_envp_list, char **words, int i)
{
	msh_del_envp(t_envp_list, words[i]);
	if (words[i + 1])
		msh_unset_worker(t_envp_list, words, i + 1);
}

void	msh_unset(char	**words, t_envp_list *envp_list)
{
	if (!words[1])
		return ;
	msh_unset_worker(envp_list, words, 1);
}
