/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redirect_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:00:29 by skorte            #+#    #+#             */
/*   Updated: 2022/06/07 14:38:26 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		write(STDOUT_FILENO, &ch, 1);
	}
	close(fd_file);
	return ;
}
