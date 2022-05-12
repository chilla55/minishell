/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:22:09 by skorte            #+#    #+#             */
/*   Updated: 2022/05/12 13:49:39 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_exe(t_exe_list *exe_list, t_envp_list *envp_list);

int main(int argc, char **argv, char **envp)
{
	t_exe_list *exe_list;
	char	*command_1 = "cat src/minishell.c";
//	char	*command_1 = "echo hello world";
	char	*command_2 = "grep h";
	char	*command_3 = "wc";

	argc++;
	argv[0] = NULL;
	exe_list = malloc(sizeof(t_exe_list));
	exe_list->argv = ft_split(command_1, ' ');
	exe_list->command = ft_strdup(exe_list->argv[0]);
	exe_list->next = malloc(sizeof(t_exe_list));
	exe_list->next->argv = ft_split(command_2, ' ');
	exe_list->next->command = ft_strdup(exe_list->next->argv[0]);
	exe_list->next->next = NULL;
	exe_list->next->next = malloc(sizeof(t_exe_list));
	exe_list->next->next->argv = ft_split(command_3, ' ');
	exe_list->next->next->command = ft_strdup(exe_list->next->next->argv[0]);
	exe_list->next->next->next = NULL;
	init_exe(exe_list, msh_create_envp_list(envp));
	msh_free_envp_list(envp_list);
	return (0);
}