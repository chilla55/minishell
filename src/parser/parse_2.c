/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 08:45:29 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/06/21 17:19:35 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_exe_list	*append_entry(char *input, t_exe_list *exe_list,
						t_envp_list *envp_list);

/*
** msh_parser 
** - takes the input string from readline,
** - inserts pipes for redirections where necessary,
** - splits the input string into an array of strings for each command,
** - sorts the array of strings to get redirection commands in right positions,
** - creates a t_exe_list with entries for each command,
** - frees the array of strings,
** - starts init_exe to run the created t_exe_list.
*/

int	msh_parser(char *input, t_envp_list *envp_list)
{
	t_exe_list	*exe_list;
	char		**input_split;
	char		**temp_split;
	char		*temp;
	int			i[2];

	exe_list = NULL;
	temp = backslash_parse(input);
	if (!check_allowed(temp))
		return (0);
	input_split = ft_split_parse(temp, '|');
	free(temp);
	i[0] = 0;
	while (input_split[i[0]])
	{
		temp = ft_insert_pipes(input_split[i[0]++]);
		temp_split = ft_split_parse(temp, '|');
		free(temp);
		i[1] = 0;
		while (temp_split[i[1]])
			exe_list = append_entry(temp_split[i[1]++], exe_list, envp_list);
		free_split(temp_split);
	}
	free_split(input_split);
	return (init_exe(exe_list, envp_list));
}

void	word_parse_2(char *input, int *i)
{
	if (input[i[0]] == '\0')
		return ;
	else if (input[i[0]] == ' ' && input[i[0] + 1] != ' ')
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
		else if (input[i[0]] == '$' && ft_strncmp(input, "<<", 2))
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

/*
** i[0] = input string length
** i[1] = counter, initialized to 0
** i[2] = word count, initialized to 1
** i[3] = toggle for single tick
** i[4] = toggle for double tick
*/

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
	reinsert_squote(words);
	free(i);
	return (words);
}

static t_exe_list	*append_entry(char *input, t_exe_list *exe_list,
				t_envp_list *envp_list)
{
	t_exe_list	*entry;

	if (!input)
		NULL;
	else if (input[0] == '\0')
		NULL;
	else if (!exe_list)
	{
		exe_list = ft_calloc(1, sizeof(t_exe_list));
		exe_list->argv = createwords(input, envp_list);
		exe_list->command = ft_strdup(exe_list->argv[0]);
	}
	else
	{
		entry = exe_list;
		while (entry->next)
			entry = entry->next;
		entry->next = ft_calloc(1, sizeof(t_exe_list));
		entry = entry->next;
		entry->argv = createwords(input, envp_list);
		entry->command = ft_strdup(entry->argv[0]);
	}
	return (exe_list);
}
