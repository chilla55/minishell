/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:00:29 by skorte            #+#    #+#             */
/*   Updated: 2022/05/21 18:11:20 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*append_line(char *input, char *line);

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
		else
			write(STDOUT_FILENO, &ch, 1);
	}
	write(STDOUT_FILENO, &ch, 1);
	close(fd_file);
	close(STDOUT_FILENO);
	return ;
}

// *** << (read input till delimiter)

void	msh_read_input_till_delimiter(char *delimiter)
{
	char	*line;
	char	*input;

	input = NULL;
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)))
			break ;
		if (!input)
			input = ft_strdup(line);
		else
			input = append_line(input, line);
		free(line);
	}
	write(STDOUT_FILENO, input, ft_strlen(input));
	write(STDOUT_FILENO, &"\n", 1);
	free(line);
	if (input)
		free(input);
	return ;
}

static char	*append_line(char *input, char *line)
{
	char	*temp;

	temp = ft_strjoin_3 (input, "\n", line);
	free(input);
	input = ft_strdup(temp);
	free(temp);
	return (input);
}
