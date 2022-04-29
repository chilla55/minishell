/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:02:39 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/04/29 09:05:56 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	inthandler(int _)
{
	char	*prompt;

	(void)_;
	ft_putstr_fd("\nTry me!:", 1);
	prompt = getcwd(NULL, 0);
	ft_putstr_fd(prompt, 1);
	free(prompt);
	ft_putstr_fd("$ ", 1);
	init_signal();
}

void	init_signal(void)
{
	struct sigaction	act;

	memset(&act, 0, sizeof(act));
	act.sa_handler = inthandler;
	sigaction(SIGINT, &act, NULL);
}
