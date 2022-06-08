/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redirect_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:00:29 by skorte            #+#    #+#             */
/*   Updated: 2022/06/08 14:57:18 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*read_input(char *delimiter);
static char	*append_line(char *input, char *line);
static char	*insert_envp(char *input, t_envp_list *envp_list);

// *** << (read input till delimiter)

void	msh_read_input_till_delimiter(char *delimiter,
			char *silent, t_envp_list *envp_list)
{
	char	*input;
	int		stdout_envp;
	int		stdout_backup;

	if (!delimiter)
	{
		write(2, "Error: no delimiter given\n", 26);
		return ;
	}
	stdout_backup = dup(STDOUT_FILENO);
	stdout_envp = ft_atoi(msh_get_envp_value(envp_list, "STDOUT_BACKUP"));
	dup2(stdout_envp, STDOUT_FILENO);
	input = read_input(delimiter);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdout_backup);
	if (input)
	{
		input = insert_envp(input, envp_list);
		input = ft_strjoin(input, "\n");
		if (!silent)
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
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
			break ;
		input = append_line(input, line);
		free(line);
	}
	if (line)
		free (line);
	printf("%s\n", input);
	return (input);
}

static char	*append_line(char *input, char *line)
{
	char	*temp;

	if (!input)
		input = ft_strdup(line);
	else
	{
		temp = ft_strjoin_3 (input, "\n", line);
		free(input);
		input = ft_strdup(temp);
		free(temp);
	}
	return (input);
}

static char	*insert_envp(char *input, t_envp_list *envp_list)
{
	char	*ptr;
	char	*envp;
	char	*temp;
	int		i;

	envp = NULL;
	i = 1;
	if (!input)
		return (NULL);
	temp = ft_strdup(input);
	ptr = ft_strchr(temp, '$');
	if (!ptr)
		return (temp);
	while (ptr)
	{
		free (input);
		input = ft_substr(temp, 0, ft_strlen(temp) - ft_strlen(ptr));
		while (ft_isalnum(ptr[i]))
			i++;
		envp = ft_substr(ptr, 1, i - 1);
		input = ft_strjoin(input, msh_get_envp_value(envp_list, envp));
		free(envp);
		if (ptr + i)
		{
			input = ft_strjoin_frees1(input, ptr + i);
			free(temp);
		}
		i = 1;
		ptr = ft_strchr(input, '$');
	}
	return (input);
}
