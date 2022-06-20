/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stdio_backups.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:55:49 by skorte            #+#    #+#             */
/*   Updated: 2022/06/21 01:10:29 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_stdio_backups(int fd_in, int fd_out, t_envp_list *envp_list)
{
	char	*stdin_envp[3];
	char	*stdout_envp[3];

	stdin_envp[0] = ft_strdup("export");
	stdin_envp[1] = ft_strjoin_frees2("STDIN_BACKUP=", ft_itoa(fd_in));
	stdin_envp[2] = NULL;
	msh_export(stdin_envp, envp_list);
	free(stdin_envp[0]);
	free(stdin_envp[1]);
	stdout_envp[0] = ft_strdup("export");
	stdout_envp[1] = ft_strjoin_frees2("STDOUT_BACKUP=", ft_itoa(fd_out));
	stdout_envp[2] = NULL;
	msh_export(stdout_envp, envp_list);
	free(stdout_envp[0]);
	free(stdout_envp[1]);
}
