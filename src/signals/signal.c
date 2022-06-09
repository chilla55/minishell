/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:02:39 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/09 17:14:49 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	inthandler(int sig)
{
	printf("\nSignal %i received\n", sig);
	if (sig == SIGQUIT)
	 	printf(" Sigquit");
	else if (sig = SIGINT)
	{
		write(1, &"\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	init_signal();
}

void	init_signal(void)
{
	struct sigaction	act;

	memset(&act, 0, sizeof(act));
	act.sa_handler = inthandler;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
