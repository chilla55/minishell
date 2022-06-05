/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:00:29 by skorte            #+#    #+#             */
/*   Updated: 2022/06/02 23:15:52 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*read_input(char *delimiter);
static char	*append_line(char *input, char *line);
static char	*insert_envp(char *input, t_envp_list *envp_list);

// *** > (append = 0) and >> (append = 1) ***

void	msh_redirect_to_file(char *path, int append)
{
	int		fd_file;
	char	ch;

	if (append)
		fd_file = open(path, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd_file = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_file == -1)
	{
		perror("open");
		return ;
	}
	while (read(STDIN_FILENO, &ch, 1) > 0)
	{
		write(fd_file, &ch, 1);
	}
	write(fd_file, &"\0", 1);
	close(fd_file);
	return ;
}

// *** < (read from file)

void	msh_read_from_file(char *path)
{
	int		fd_file;
	char	ch;

	fd_file = open(path, O_RDONLY);
	if (fd_file == -1)
	{
		perror("open");
		return ;
	}
	while (read(fd_file, &ch, 1) > 0)
	{	
		if (ch == '\n')
		{
			if (read(fd_file, &ch, 1) > 0)
				write(STDOUT_FILENO, &"\n", 1);
		}
		write(STDOUT_FILENO, &ch, 1);
	}
	close(fd_file);
	return ;
}

// *** << (read input till delimiter)

void	msh_read_input_till_delimiter(char *delimiter,
			char *silent, t_envp_list *envp_list)
{
	char	*input;
	char 	*input_2;
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
	input_2 = insert_envp(input, envp_list);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdout_backup);
	if (!silent)
	{
		write(STDOUT_FILENO, input_2, ft_strlen(input_2));
		write(STDOUT_FILENO, &"\n", 1);
	}
	if (input)
		free(input);
	if (input_2)
		free(input_2);
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
	free(line);
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
	temp = NULL;
	i = 1;
	if (!input)
		return (NULL);
	ptr = ft_strchr(input, '$');
	if (!ptr)
		return (input);
	while (ptr)
	{
		temp = ft_substr(input, 0, ft_strlen(input) - ft_strlen(ptr));
//		printf(" %s \n", temp);
		while (ft_isalnum(ptr[i]))
			i++;
		envp = ft_substr(ptr, 1, i - 1);
		printf("get %s :\n %s ***\n", envp, msh_get_envp_value(envp_list, envp));
		temp = ft_strjoin(temp, msh_get_envp_value(envp_list, envp));
//		printf(" %s \n", temp);
		free(envp);
		if (ptr + i)
			input = ft_strjoin(temp, ptr + i);
//		printf("***%s***\n", input);
		ptr = ft_strchr(input, '$');
	}
	return (input);
//	free(input);
//	return (NULL);//msh_get_envp_value(envp_list, envp));
}
