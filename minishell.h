/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 11:03:55 by skorte            #+#    #+#             */
/*   Updated: 2022/04/21 19:42:49 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*****************************************************************************/
/*
** Program name: minishell
**
** Turn in files: Makefile, *.h, *.c
**
** Makefile: NAME, all, clean, fclean, re
**
** Arguments: none
**
** External functs.:
**	readline, rl_clear_history, rl_on_new_line,
**	rl_replace_line, rl_redisplay, add_history,
**	printf, malloc, free, write, access, open, read,
**	close, fork, wait, waitpid, wait3, wait4, signal,
**	sigaction, sigemptyset, sigaddset, kill, exit,
**	getcwd, chdir, stat, lstat, fstat, unlink, execve,
**	dup, dup2, pipe, opendir, readdir, closedir,
**	strerror, perror, isatty, ttyname, ttyslot, ioctl,
**	getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
**	tgetnum, tgetstr, tgoto, tputs
**
** Libft authorized: Yes
**
** Description: Write a shell
*/
/*****************************************************************************/

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
// readline, rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history
# include <stdio.h>
// printf
# include <stdlib.h>	
// malloc, free, exit
// getenv (get an environment variable)
# include <unistd.h>
// write, access, read, close, fork,
// getcwd, chdir (get complete directory, change directory),
// unlink (deletes a name from the filesystem),
// execve, pipe,
// dub, dub2 (duplicate a file descriptor),
// isatty (returns 1 if fd is an open file descriptor referring to a
//  terminal; otherwise 0 is returned, and errno is set to indicate the error),
// ttyname (returns a pointer to the null-terminated pathname),
// ttyslot (https://man7.org/linux/man-pages/man3/ttyslot.3.html ???)
# include <fcntl.h>
// open
# include <sys/wait.h>
// wait, waitpid, wait3, wait4
# include <signal.h>
// signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h>
// stat, lstat, fstat (return information about a file)
# include <dirent.h>
// opendir, readdir, closedir
// see (https://man7.org/linux/man-pages/man3/readdir.3.html)
# include <string.h>
// strerror
# include <errno.h>
// perror (also stdio.h)
# include <sys/ioctl.h>
// ioctl (https://man7.org/linux/man-pages/man2/ioctl.2.html)
# include <termios.h>
// tcsetattr, tcgetattr (???)
# include <curses.h>
# include <term.h>
// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
// (https://man7.org/linux/man-pages/man3/tgetent.3x.html ???)

# include "libft/libft.h"

#endif