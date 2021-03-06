/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:02:39 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/14 14:24:17 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
