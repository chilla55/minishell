/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:02:39 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/04/27 08:08:51 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	inthandler(int i)
{
	struct sigaction	act;

	(void) i;
	write(1, "\nTry me!$ ", 11);
	act.sa_handler = inthandler;
	sigaction(SIGINT, &act, NULL);
}

void	init_signal(void)
{
	struct sigaction	act;

	act.sa_handler = inthandler;
	sigaction(SIGINT, &act, NULL);
}
