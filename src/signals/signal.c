/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:02:39 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/09 14:37:54 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	inthandler(int _)
{
	(void)_;
	write(1, &"\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	init_signal();
}

void	init_signal(void)
{
	struct sigaction	act;

	memset(&act, 0, sizeof(act));
	act.sa_handler = inthandler;
	sigaction(SIGINT, &act, NULL);
}
