/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 11:03:55 by skorte            #+#    #+#             */
/*   Updated: 2022/06/21 23:40:27 by skorte           ###   ########.fr       */
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

# include <stdio.h>
// printf
# include <readline/readline.h>
# include <readline/history.h>
// readline, rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history
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

# include "../includes/libft/src/libft.h"

typedef struct s_envp_list
{
	char				*name;
	char				*value;
	struct s_envp_list	*next;
}					t_envp_list;

typedef struct s_exe_list
{
	char				*command;
	char				**argv;
	struct s_exe_list	*next;
}					t_exe_list;

// main.c
void		msh_free_envp_list(t_envp_list *envp_list);

// parser/parse.c
char		*squote_parse(char *input, int *i);
char		*env_parse(char *input, int *i, t_envp_list *envp_list);
char		*dquote_parse(char *input, int *i, t_envp_list *envp_list);

// parser/parse_2.c
int			msh_parser(char *input, t_envp_list *envp_list);

// parse/ft_split_parse.c
char		**ft_split_parse(char const *s, char c);

// parser/parse_3_redirections.c
char		*ft_insert_pipes(char *input);

// parser/parse_3_redirections_2.c
char		*insert_space_after_redir(char *input);
char		*check_if_command(char *input);
int			find_word_end(char *temp, int i);
void		test_quotes(char *str, int i, int	*sq, int *dq);

// parser/parse_4.c
int			check_allowed(char *input);
void		reinsert_squote(char **words);

// parser/parse_5.c
char		**prepare_split_input(char *input);

// env/envp_create.c
t_envp_list	*msh_create_envp_list(char **envp);
t_envp_list	*msh_copy_envp_list(t_envp_list *old_envp_list);
char		**msh_create_envp_from_list(t_envp_list *envp_list);

// env/envp_del.c
int			msh_del_envp(t_envp_list *envp_list, char *name);

// env/envp_get.c
t_envp_list	*msh_get_envp_ptr(t_envp_list *envp_list, char *name);
char		*msh_get_envp_name(char *content);
char		*msh_get_envp_value(t_envp_list *envp_list, char *name);

// env/envp_lst_new.c
t_envp_list	*msh_envp_lstnew(char *content);
t_envp_list	*msh_envp_lstnew_2(char *name, char *value);

// env/envp_set.c
int			msh_set_envp(t_envp_list *envp_list,
				char *name, char *value, int overwrite);
int			msh_set_envp_free_value(t_envp_list *envp_list, char *name,
				char *value, int overwrite);

// env/envp_utils.c
int			msh_exist_envp(t_envp_list *envp_list, char *name);
int			msh_print_envp_list(t_envp_list *envp_list);
int			msh_envp_lstsize(t_envp_list *lst);

//void		msh_redirect_to_file(char *path, int append);
//void		msh_read_from_file(char *path);

// builtins/msh_pwd.c
char		*msh_pwd(void);
void		msh_pwd_cmd(void);

// builtins/msh_echo.c
void		msh_echo(char **argv);

// builtins/msh_cd.c
void		msh_cd(char **argv);

// builtins/msh_export.c
void		msh_export(char	**words, t_envp_list *envp_list);
void		free_split(char **strarr);

// builtins/msh_unset.c
void		msh_unset(char	**words, t_envp_list *envp_list);

// builtins/mash_env.c
void		msh_env(char **words, t_envp_list *envp_list);

// builtins/msh_redirections.c
void		msh_redirect_to_file(char *path, int append);
void		msh_read_from_file(char *path);
void		msh_read_input_till_delimiter(char *delimiter,
				t_envp_list *envp_list);

// signals/signal_handler.c
void		handler_sigquit(int sig);
void		handler_sigint_inter(int sig);
void		handler_sigint_active(int sig);

// signals/signal.c
void		signal_child(void);
void		signal_inter(void);
void		signal_active(void);

// pipes/run_exe_list.c
int			init_exe(t_exe_list *exe_list, t_envp_list *envp_list);
int			run_exe_list(t_exe_list *exe_list, t_envp_list *envp_list,
				int fd_in, int fd_out);

// pipes/run_command.c
int			run_command(t_exe_list *exe_list_element, t_envp_list *envp_list);
int			run_export(t_exe_list *exe_list, t_envp_list *envp_list);

// utils/msh_free.c
void		free_paths(char **paths);
void		free_exe_list(t_exe_list *exe_list);
void		free_str(char *str);

// utils/stdio_backups.c
void		create_stdio_backups(int fd_in, int fd_out, t_envp_list *envp_list);

// utils/export_util.c
char		**export_str_split(char *str, char c);
int			str_contains_str(char *str, char *contains);

// utils/string_utils.c
char		*join_try_free(char *a, char *b);
char		*ft_strinsertchar(char *str, char c, int pos);
char		*ft_strdelchar(char *str, int pos);

#endif