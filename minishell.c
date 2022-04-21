/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:16:11 by skorte            #+#    #+#             */
/*   Updated: 2022/04/21 11:27:16 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	*input;
	char	*prompt;
	int		exit;

	printf("Hello World! One day, I will be a true MiniShell...\n");
	prompt = "Try me!$ ";
	exit = 0;
	while (!exit)
    {
    	input = readline(prompt);
    	/* If there is anything on the line, print it and remember it. */
    	if (*input)
		{
			printf ("%s\n", input);
			add_history (input);
		}
    	/* Check for `command' "exit" */
    	if (ft_strncmp(input, "exit", 5) == 0)
			exit = 1;
    	/* Check for `command' "list" to print history */
	    if (ft_strncmp(input, "list", 5) == 0)
		{
			HIST_ENTRY **list;
			register int i;
			list = history_list ();
			i = 0;
			if (list)
				while(list[i])
				{
					printf ("%d: %s\n", i, list[i]->line);
					i++;
				}
		}
    free (input);
	}
	clear_history();
	return (0);
}
