/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 08:45:29 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/05/31 22:39:58 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strinsertchar(char *str, char c, int pos);
int		ft_find_word_end(char *temp, int i);
char	*ft_insert_pipes(char *input);
void	ft_sort_redirections(char **split);

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
	free(i);
	return (words);
}

t_exe_list	*createentry(char *input, t_envp_list *envp_list)
{
	t_exe_list	*entry;

	if (!input)
		return (NULL);
	if (input[0] == '\0')
		return (NULL);
	entry = ft_calloc(1, sizeof(t_exe_list));
	entry->argv = createwords(input, envp_list);
	entry->command = ft_strdup(entry->argv[0]);
	printf("creating %s\n", input);
	return (entry);
}

t_exe_list	*createentry_2(char *input, t_envp_list *envp_list)
{
	char		*input_1;
	char		*input_2;
	int			length;
	t_exe_list	*entry;

	input_1 = NULL;
	input_2 = NULL;
	entry = NULL;
	if (ft_strchr(input, '>'))
	{
		input_2 = ft_strdup(ft_strchr(input, '>'));
		length = ft_strlen(input) - ft_strlen(input_2);
		if (length)
		{
			input_1 = malloc(sizeof(char) * (length + 1));
			ft_strlcpy(input_1, input, length + 1);
		}
	}
	else if (ft_strchr(input, '<'))
	{
		input_1 = ft_strdup(ft_strchr(input, '<'));
		length = ft_strlen(input) - ft_strlen(input_1);
		if (length)
		{
			input_2 = malloc(sizeof(char) * (length + 1));
			ft_strlcpy(input_2, input, length);
		}
	}
	else
	{
		return (createentry(input, envp_list));
	}
	entry = createentry(input_1, envp_list);
	if (entry)
		entry->next = createentry(input_2, envp_list);
	else
		entry = createentry(input_2, envp_list);
	return (entry);
}

int	msh_parser(char *input, t_envp_list *envp_list)
{
	t_exe_list	*exe_list;
	t_exe_list	*exe_work;
	char		**input_split;
	char		*temp;
	int			i;

	i = 0;
	temp = ft_insert_pipes(input);
	input_split = ft_split_parse(temp, '|');
	ft_sort_redirections(input_split);
	while (input_split[i])
	{
		if (i == 0)
		{
			exe_list = createentry_2(input_split[i], envp_list);
			exe_work = exe_list;
			i++;
			continue ;
		}
		while (exe_work->next)
			exe_work = exe_work->next;
		exe_work->next = createentry_2(input_split[i], envp_list);
		exe_work = exe_work->next;
		i++;
	}
	free_split(input_split);
	init_exe(exe_list, envp_list);
	return (0);
}

char	*ft_insert_pipes(char *input)
{
	char	*temp;
	int		sq;
	int		dq;
	int		i;

	sq = 0;
	dq = 0;
	i = 0;
	temp = ft_strdup(input);
	if (!ft_strncmp(temp, "<<", 2))
	{
		i = i + 2;
		temp = ft_strinsertchar(temp, ' ', i);
		i = ft_find_word_end(temp, i);
		temp = ft_strinsertchar(temp, ' ', i);
		i++;
		temp = ft_strinsertchar(temp, 's', i);
		i++;
		temp = ft_strinsertchar(temp, '|', i);
	}
	else if (temp[0] == '<' || temp[0] == '>')
		temp = ft_strjoin_frees2("echo -n \"\" ", temp);
	while (temp[i])
	{
		if (temp[i] == '\'' && !dq)
				sq = (sq + 1) % 2;
		else if (temp[i] == '\"' && !sq)
				dq = (dq + 1) % 2;
		else if ((temp[i] == '<' && temp[i + 1] == '<' && !sq && !dq )
				||( temp[i] == '>' && temp[i + 1] == '>' && !sq && !dq ))
		{
			temp = ft_strinsertchar(temp, '|', i);
			i = i + 3;
			temp = ft_strinsertchar(temp, ' ', i);
			i = ft_find_word_end(temp, i);
			temp = ft_strinsertchar(temp, '|', i);
		}
		else if ((temp[i] == '<' || temp[i] == '>') && !sq && !dq )
		{
			temp = ft_strinsertchar(temp, '|', i);
			i = i + 2;
			temp = ft_strinsertchar(temp, ' ', i);
			i = ft_find_word_end(temp, i);
			temp = ft_strinsertchar(temp, '|', i);
		}
		i++;
	}
	return (temp);
}

void	ft_sort_redirections(char **split)
{
	int		i;
	char	*temp;

	i = 1;
	while (split[i])
	{
		if (split[i][0] == '<')
		{
			temp = split[i];
			split[i] = split[i - 1];
			split[i - 1] = temp;
		}
		i++;
	}
}

char	*ft_strinsertchar(char *str, char c, int pos)
{
	char	*str1;
	char	*str2;
	char	*c_str;
	char	*dest;
	
	if (!str)
		return (NULL);
	if (pos > (int)ft_strlen(str))
		pos = ft_strlen(str);
	str1 = ft_substr(str, 0, pos);
	str2 = ft_substr(str, pos, ft_strlen(str) - pos);
	c_str = malloc(2 * sizeof(char));
	c_str[0] = c;
	c_str[1] = '\0';
	dest = ft_strjoin_3(str1, c_str, str2);
	free(c_str);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (dest);
}

int		ft_find_word_end(char *temp, int i)
{
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	while (temp[i] == ' ')
		i++;
	while (temp[i] != ' ' || sq || dq )
	{
		if (temp[i] == '\0')
			break ;
		else if (temp[i] == '\'' && !dq)
			sq = (sq + 1) % 2;
		else if (temp[i] == '\"' && !sq)
			dq = (dq + 1) % 2;
		i++;
	}
	return (i);
}
