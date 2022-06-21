/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 08:45:29 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/21 15:41:15 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** insert_pipes takes the input, searches for redirections and inserts pipes.
** The redirections are then executed like built-in functions
** in their own child processes.
**
** If a pipe is the first element of the input, echo -n "" is put in front.
** This is necessary to give the redirection an empty source/silent drain.
**
** When searching the input for < or >, quotes have to be interpreted.
** If an unquoted < or > is found, insert_here is started to change the
** input string as needed.
*/

static void	input_redirect_pipe(char **input, char **redirections, int i);
static void	output_redirect_pipe(char **input, char **redirections, int i);
static char	*redirect_pipe_join(char **command, char **in_red, char **out_red);

char	*ft_insert_pipes(char *input)
{
	char	*temp[3];
	int		sq;
	int		dq;
	int		i;

	sq = 0;
	dq = 0;
	i = 0;
	temp[0] = insert_space_after_redir(input);
	temp[1] = NULL;
	temp[2] = NULL;
	while (temp[0][i])
	{
		if (temp[0][i] == '<' && !sq && !dq)
			input_redirect_pipe(&temp[0], &temp[1], i);
		else if (temp[0][i] == '>' && !sq && !dq)
			output_redirect_pipe(&temp[0], &temp[2], i);
		else
		{
			test_quotes(temp[0], i, &sq, &dq);
			i++;
		}
	}
	return (redirect_pipe_join(&temp[0], &temp[1], &temp[2]));
}

static void	input_redirect_pipe(char **input, char **redirections, int i)
{
	int		j;
	char	*temp;

	j = find_word_end(*input, i);
	temp = ft_strjoin_frees2(*redirections, ft_substr(*input, i, j - i));
	if (*redirections)
		free(*redirections);
	*redirections = ft_strjoin_frees1(temp, " | ");
	temp = ft_strjoin_free(ft_substr(*input, 0, i),
			ft_substr(*input, j, ft_strlen(*input) - j));
	free(*input);
	*input = temp;
}

static void	output_redirect_pipe(char **input, char **redirections, int i)
{
	int		j;
	char	*temp;

	j = find_word_end(*input, i);
	temp = ft_strjoin_frees1(ft_strdup(" | "), *redirections);
	if (*redirections)
		free(*redirections);
	*redirections = ft_strjoin_free(temp, ft_substr(*input, i, j - i));
	temp = ft_strjoin_free(ft_substr(*input, 0, i),
			ft_substr(*input, j, ft_strlen(*input) - j));
	free (*input);
	*input = temp;
}

static char	*redirect_pipe_join(char **command, char **in_red, char **out_red)
{
	*command = check_if_command(*command);
	*command = ft_strjoin_frees2(*in_red, *command);
	*command = ft_strjoin_frees1(*command, *out_red);
	free(*in_red);
	free(*out_red);
	return (*command);
}
