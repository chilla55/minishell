/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 08:45:29 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/05/13 08:47:59 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	word_parse_2(char *input, int *i)
{
	if (input[i[0]] == ' ' && input[i[0] + 1] != ' ')
		i[3] = i[0] + 1;
	else if (input[i[0]] != ' ' && (input[i[0] + 1] == ' '
			|| !input[i[0] + 1]) && i[0] != i[3])
		i[1]++;
}

void	word_parse(char *input, char **words, int inlen, t_envp_list *envp_list)
{
	int	*i;

	i = ft_calloc(4, sizeof(int));
	while (i[0] < inlen)
	{
		if (input[i[0]] == '\'')
			words[i[1]] = join_try_free(words[i[1]], squote_parse(input, i));
		else if (input[i[0]] == '\"')
			words[i[1]] = join_try_free(words[i[1]],
					dquote_parse(input, i, envp_list));
		else if (input[i[0]] == '$')
			words[i[1]] = join_try_free(words[i[1]],
					env_parse(input, i, envp_list));
		else if (input[i[0]] != ' ')
		{
			words[i[1]] = join_try_free(words[i[1]],
					ft_substr(input, i[3], i[0] - i[3] + 1));
			i[3] = i[0] + 1;
		}
		word_parse_2(input, i);
		i[0]++;
	}
	free(i);
}

char	**createwords(char *input, t_envp_list *envp_list)
{
	char	**words;
	int		*i;

	i = ft_calloc(5, sizeof(int));
	i[0] = ft_strlen(input);
	i[2] = 1;
	while (i[1] < i[0])
	{
		if (input[i[1]] == '\'' && !i[4])
				i[3] = (i[3] + 1) % 2;
		else if (input[i[1]] == '\"' && !i[3])
				i[4] = (i[4] + 1) % 2;
		if (input[i[1]] == ' ' && input[i[1] + 1] != ' '
			&& i[3] == 0 && i[4] == 0)
			i[2]++;
		i[1]++;
	}
	words = ft_calloc(i[2] + 1, sizeof(char *));
	word_parse(input, words, i[0], envp_list);
	free(i);
	return (words);
}

t_exe_list	*createentry(char *input, t_envp_list *envp_list)
{
	t_exe_list	*entry;

	entry = ft_calloc(1, sizeof(t_exe_list));
	entry->argv = createwords(input, envp_list);
	entry->command = ft_strdup(entry->argv[0]);
	return (entry);
}

int	msh_parser(char *input, t_envp_list *envp_list)
{
	t_exe_list	*exe_list;
	t_exe_list	*exe_work;
	char		**input_split;
	int			i;

	i = 0;
	input_split = ft_split_parse(input, '|');
	while (input_split[i])
	{
		if (i == 0)
		{
			exe_list = createentry(input_split[i], envp_list);
			exe_work = exe_list;
			i++;
			continue ;
		}
		exe_work->next = createentry(input_split[i], envp_list);
		exe_work = exe_work->next;
		i++;
	}
	free_split(input_split);
	init_exe(exe_list, envp_list);
	return (0);
}
