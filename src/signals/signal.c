/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:02:39 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/10 00:29:50 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handler_sigquit(struct readline_state *sp)
{
	if (sp->end)
	{
		write(1, &"QUIT\n", 5);
		rl_replace_line("exit", 0);
		rl_done = 1;
	}
	else
		write(1, "\b\b  \b\b", 6);
}

static void	handler_sigint(void)
{
	if (!rl_done)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
	else
		write(1, &"\n", 1);
}

static void	inthandler(int sig)
{
	struct readline_state	*sp;

	sp = malloc(sizeof(struct readline_state));
	rl_save_state(sp);
	if (sig == SIGQUIT)
		handler_sigquit(sp);
	else if (sig == SIGINT)
		handler_sigint();
	init_signal();
}

int	event(void)
{
	return (0);
}

/*
** ctrl+C = SIGINT
** ctrl+\ = SIGQUIT
** ctrl+D = EOF (NOT A SIGNAL!)
*/

void	init_signal(void)
{
	struct sigaction	act;

	memset(&act, 0, sizeof(act));
	act.sa_handler = inthandler;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	rl_event_hook = event;
}
