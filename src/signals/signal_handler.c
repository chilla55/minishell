/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:24:02 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/14 14:26:17 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		write(1, &"QUIT\n", 5);
		rl_replace_line("exit", 0);
	}
}

void	handler_sigint_inter(int sig)
{
	if (sig == SIGINT)
	{
		write(1, &"\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handler_sigint_active(int sig)
{
	if (sig == SIGINT)
	{
		write(1, &"\n", 1);
		rl_replace_line("", 0);
	}
}
