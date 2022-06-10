/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:02:39 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/10 18:09:13 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handler_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		write(1, &"QUIT\n", 5);
		rl_replace_line("exit", 0);
	}
}

static void	handler_sigint_inter(int sig)
{
	if (sig == SIGINT)
	{
		write(1, &"\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	handler_sigint_active(int sig)
{
	if (sig == SIGINT)
	{
		write(1, &"\n", 1);
		rl_replace_line("", 0);
	}
}

/*
** ctrl+C = SIGINT
** ctrl+\ = SIGQUIT
** ctrl+D = EOF (NOT A SIGNAL!)
*/

void	signal_active(void)
{
	signal(SIGINT, &handler_sigint_active);
	signal(SIGQUIT, &handler_sigquit);
}

void	signal_inter(void)
{
	signal(SIGINT, &handler_sigint_inter);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
