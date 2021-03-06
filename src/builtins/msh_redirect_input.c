/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redirect_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:00:29 by skorte            #+#    #+#             */
/*   Updated: 2022/06/21 01:06:41 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*read_input(char *delimiter);
static char	*append_line(char *input, char *line);
static char	*insert_envp(char *input, t_envp_list *envp_list);
static char	*insert_envp_2(char *input, char *ptr, t_envp_list *envp_list);

// *** << (read input till delimiter)

void	msh_read_input_till_delimiter(char *delimiter, t_envp_list *envp_list)
{
	char	*input;
	int		stdio_backup[2];

	if (!delimiter)
	{
		write(2, "Error: no delimiter given\n", 26);
		return ;
	}
	stdio_backup[0] = dup(STDOUT_FILENO);
	stdio_backup[1] = dup(STDIN_FILENO);
	dup2(ft_atoi(msh_get_envp_value(envp_list, "STDOUT_BACKUP")),
		STDOUT_FILENO);
	dup2(ft_atoi(msh_get_envp_value(envp_list, "STDIN_BACKUP")), STDIN_FILENO);
	input = read_input(delimiter);
	dup2(stdio_backup[0], STDOUT_FILENO);
	close(stdio_backup[0]);
	dup2(stdio_backup[1], STDIN_FILENO);
	close(stdio_backup[1]);
	if (input)
	{
		input = ft_strjoin_frees1(insert_envp(input, envp_list), "\n");
		write(STDOUT_FILENO, input, ft_strlen(input));
		free(input);
	}
	return ;
}

static char	*read_input(char *delimiter)
{
	char	*line;
	char	*input;

	input = NULL;
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(2, "\n> warning: here-document delimited by end-of-file\n", 51);
			break ;
		}
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			break ;
		input = append_line(input, line);
		free(line);
	}
	if (line)
		free (line);
	return (input);
}

static char	*append_line(char *input, char *line)
{
	char	*temp;

	if (!input)
		input = ft_strdup(line);
	else
	{
		temp = ft_strjoin_3(input, "\n", line);
		free(input);
		input = ft_strdup(temp);
		free(temp);
	}
	return (input);
}

static char	*insert_envp(char *input, t_envp_list *envp_list)
{
	char	*ptr;

	if (!input)
		return (NULL);
	ptr = input;
	while (ptr[0] && (ptr[0] != '$'
			|| (!ft_isalnum(ptr[1]) && ptr[1] != '?')))
		ptr++;
	while (ptr[0] && ptr[1])
	{
		if (ptr[0] == '$')
			input = insert_envp_2(input, ptr, envp_list);
		ptr = input;
		while (ptr[0] && (ptr[0] != '$'
				|| (!ft_isalnum(ptr[1]) && ptr[1] != '?')))
			ptr++;
	}
	return (input);
}

static char	*insert_envp_2(char *input, char *ptr, t_envp_list *envp_list)
{
	char	*temp;
	char	*temp_2;
	char	*envp;
	char	*output;
	int		i;

	i = 1;
	temp = ft_substr(input, 0, ft_strlen(input) - ft_strlen(ptr));
	temp_2 = NULL;
	while (ft_isalnum(ptr[i]))
		i++;
	envp = ft_substr(ptr, 1, i - 1);
	temp_2 = ft_strdup(msh_get_envp_value(envp_list, envp));
	if (temp_2)
		output = ft_strjoin_3(temp, temp_2, ptr + i);
	else
		output = ft_strjoin(temp, ptr + i);
	if (envp)
		free(envp);
	if (temp)
		free(temp);
	if (temp_2)
		free(temp_2);
	free(input);
	return (output);
}
